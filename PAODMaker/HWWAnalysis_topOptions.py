# =============================================================================
#  Name:        HWWAnalysis_topOptions.py
#
#  Author:      Karsten Koeneke
#  Created:     August 2014
#
#  Usage: Here, all neccessary job options for the HWW analysis can be set.
#         To run, type:
#              athena PhysicsxAODConfig/HWWAnalysis_topOptions.py 2>&1 | tee log.txt
# =============================================================================

# Import the error handling
#svcMgr.CoreDumpSvc.FatalHandler = 438
#import traceback

# To change the print format, leave 40 characters before "INFO",...
MessageSvc.Format = "% F%60W%S%7W%R%T %0W%M"

# Set a very high limit on the number of messages allowed - useful for debugging
#MessageSvc.defaultLimit = 9999999

# delete file catalog at beginning of job options
# Fix for issue documented in https://groups.cern.ch/group/hn-atlas-dist-analysis-help/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fhn%2Datlas%2Ddist%2Danalysis%2Dhelp%2FLists%2FArchive%2FJob%20with%20Error%20Cannot%20load%20branch%20DataHeaderForm%20finishes&FolderCTID=0x01200200FB8F64B0E343CB4680DEAC546A9DF813
# linked to a similar previous question in https://groups.cern.ch/group/hn-atlas-PATHelp/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fhn%2Datlas%2DPATHelp%2FLists%2FArchive%2FFailed%20to%20call%20beginInputFile%20due%20to%20AthenaPoolConvertor&FolderCTID=0x0120020084D7E80CB0C3394A8D54EF07C309B044
if os.path.exists('PoolFileCatalog.xml'):
    os.unlink('PoolFileCatalog.xml')

# Set up (Py)ROOT.
import ROOT
ROOT.xAOD.Init().ignore()

# Force-load some xAOD dictionaries. To avoid issues from ROOT-10940.
ROOT.xAOD.Jet()

# Import the steering flags for this analysis
from PhysicsxAODConfig.HWWCommonAnalysisFlags import hWWCommon

# for messaging
from AthenaCommon.Logging import logging
hWW_msg = logging.getLogger( 'HWWAnalysis' )
hWWCommon.Global.logLevel = vars().get('PAODLogLevel', INFO) # 3=INFO, 2=DEBUG
hWW_msg.setLevel(hWWCommon.Global.logLevel)


# ==============================================================================
# Load your input file that you want to process.
# Note that the last method gets the highest priority.
# ==============================================================================
from AthenaCommon.AthenaCommonFlags import jobproperties as jp
import AthenaPoolCnvSvc.ReadAthenaPool
from glob import glob
from PhysicsxAODConfig.HWWCommonHelpers import search_file

myFileList = ["/eos/user/l/lihao/PxAODMaker_file/mc16e/mc16_13TeV/DAOD_HIGG5D2.31822308._000026.pool.root.1"]

envVar = "DataMC"
# envVar = "SharedDataMC"
if os.getenv(envVar) and os.path.exists(os.getenv(envVar)) :
    basePath = os.getenv(envVar)+"/DxAOD/rel20p7/mc15_13TeV.341080.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_WWlvlv_EF_15_5.merge.DAOD_HIGG3D1.e3871_s2608_s2183_r7772_r7676_p3042/"
    #basePath = os.getenv(envVar)+"/DxAOD/rel20p7/data15_13TeV.00284154.physics_Main.merge.DAOD_HIGG3D1.r7562_p2521_p2667/"
    #basePath = os.getenv(envVar)+"/DxAOD/rel20p7/data16_13TeV.periodB3.physics_Main.PhysCont.DAOD_HIGG3D1.grp16_v01_p2667/"
    myFileList = glob( basePath+"*.root*")
    pass
# For local running
if vars().has_key('INDIR'):
    inDir = vars().get('INDIR')
    if os.path.exists(inDir): myFileList = glob(inDir+"/*.root*")
    else: hWW_msg.warning("Provided directory '%s' does not exist. Using input files: %s" % (inDir, myFileList))
    pass
if vars().has_key('INFILELIST'):
    inFileStringList = vars().get('INFILELIST')
    inFileList = inFileStringList.split(',')
    myFileList = inFileList
    pass
if vars().has_key('INTEXTFILE'):
    fileName = vars().get('INTEXTFILE')
    tmpFileList = []
    # Test if the file exists
    if not os.path.isfile(fileName):
        # Check if CMake has automatically installed the file such that it is available in $PATH
        search_path = os.environ["PATH"]
        fileName = search_file(fileName, search_path)
        if not fileName:
            hWW_msg.warning("Provided input text file '%s' does not exist...." % fileName)
    # If the file exists, we can quickly open it in read-only mode
    if fileName:
        with open(fileName,'r') as fileObject:
            for line in fileObject: tmpFileList.append(line.rstrip('\n'))
            pass
        pass
    myFileList = tmpFileList
    pass
if vars().has_key('INFILE'):
    inFile = vars().get('INFILE')
    if os.path.exists(inFile): myFileList = [inFile]
    else: hWW_msg.warning("Provided input file '%s' does not exist. Using input files: %s" % (inFile, myFileList))
    pass
hWW_msg.info("Using %i input files: %s" % (len(myFileList), myFileList))
jp.AthenaCommonFlags.FilesInput = myFileList


# ==============================================================================
# Fetch the AthAlgSeq, i.e., one of the existing master sequences where one should attach all algorithms
# ==============================================================================
topSequence = CfgMgr.AthSequencer("AthAlgSeq", OutputLevel = WARNING)


# ==============================================================================
# Perform some commonly needed tasks
# ==============================================================================
svcMgr.EventSelector.InputCollections = jp.AthenaCommonFlags.FilesInput()
svcMgr.StatusCodeSvc.AbortOnError=True

# Import the reading of in-file metadata
from PyUtils import AthFile
af = AthFile.fopen( svcMgr.EventSelector.InputCollections[0] )
eventDataItems = []
for evtItem in af.fileinfos["eventdata_items"]:
    evtItem0 = evtItem[0]
    if evtItem[0] == None :
        hWW_msg.info("Got an unknown type from the input file for the item with name: %s" % evtItem[1])
        evtItem0 = "None"
    eventDataItems.append( evtItem0 + "#" + evtItem[1] )
    pass



# ==============================================================================
# Schedule the bookkeeping of the number of processed events and sum-of-weights
# ==============================================================================
from EventBookkeeperTools.CutFlowHelpers import CreateCutFlowSvc
CreateCutFlowSvc( svcName="CutFlowSvc", athFile=af, seq=topSequence, addMetaDataToAllOutputFiles=True )
# svcMgr.CutFlowSvc.OutputLevel = VERBOSE

# Also add an instance of the CutFlowSvc for all other CutBookkeeperContainers
# and add the resulting containers to all output streams/files
inputStreamName = af.fileinfos["stream_names"][0]
if not hasattr(svcMgr,"CutFlowSvc"): svcMgr += CfgMgr.CutFlowSvc()
svcMgr.CutFlowSvc.InputStream = inputStreamName
theApp.CreateSvc += ['CutFlowSvc/CutFlowSvc']
from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperContainer#CutBookkeepers")
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperAuxContainer#CutBookkeepers*")
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperContainer#IncompleteCutBookkeepers")
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperAuxContainer#IncompleteCutBookkeepers*")
for mdItem in af.fileinfos["metadata_items"]:
    if mdItem[0].startswith("xAOD::CutBookkeeperContainer") \
      and not mdItem[1] == "CutBookkeepers"                 \
      and not mdItem[1].startswith("Incomplete") :
        cbkName = mdItem[1]
        hWW_msg.info("Creating now a CutFlowSvc instance for CutBookkeeperContainer with name %s" % cbkName)
        cfsName = "CutFlowSvc"+cbkName
        svcMgr += CfgMgr.CutFlowSvc(cfsName,
                                    #OutputLevel              = WARNING,
                                    InputStream              = inputStreamName,
                                    OutputCollName           = cbkName,
                                    OutputIncompleteCollName = "Incomplete"+cbkName
                                    )
        theApp.CreateSvc += [ "CutFlowSvc/"+cfsName ]
        MSMgr.AddMetaDataItemToAllStreams( "xAOD::CutBookkeeperContainer#"+cbkName )
        MSMgr.AddMetaDataItemToAllStreams( "xAOD::CutBookkeeperAuxContainer#"+cbkName+"*" )
        pass
    pass

### Update also the other counters for the non-nominal MC weights
topSequence.AllExecutedEvents.BookkeepOtherMCEventWeights = True

# For the correct handling of the trigger meta-data
ToolSvc += CfgMgr.xAODMaker__TriggerMenuMetaDataTool("TriggerMenuMetaDataTool")
svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.TriggerMenuMetaDataTool ]

# For the correct handling of the luminosity blocks meta-data
ToolSvc += CfgMgr.LumiBlockMetaDataTool("LumiBlockMetaDataTool")
svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.LumiBlockMetaDataTool ]
MSMgr.AddMetaDataItemToAllStreams("xAOD::LumiBlockRangeContainer#*")
MSMgr.AddMetaDataItemToAllStreams("xAOD::LumiBlockRangeAuxContainer#*")

# For the correct handling of the xAOD::EventFormat (required to read file in ROOT)
ToolSvc += CfgMgr.xAODMaker__EventFormatMetaDataTool( "EventFormatMetaDataTool" )
svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.EventFormatMetaDataTool ]

# Set up the FileMetaData tool:
ToolSvc += CfgMgr.xAODMaker__FileMetaDataCreatorTool( "FileMetaDataCreatorTool" )
svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.FileMetaDataCreatorTool ]
MSMgr.AddMetaDataItemToAllStreams("xAOD::FileMetaData#FileMetaData")
MSMgr.AddMetaDataItemToAllStreams("xAOD::FileMetaDataAuxInfo#FileMetaDataAux." )

# Set up the TruthMetaData tool:
ToolSvc += CfgMgr.xAODMaker__TruthMetaDataTool( "TruthMetaDataTool" )
svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.TruthMetaDataTool ]
MSMgr.AddMetaDataItemToAllStreams("xAOD::TruthMetaDataContainer#TruthMetaData")
MSMgr.AddMetaDataItemToAllStreams("xAOD::TruthMetaDataAuxContainer#TruthMetaDataAux." )

# ==============================================================================
# If you have your own analysis scripts
# (for examples, see in svn: PhysicsAnalysis/MyPackage/share/MySuperJobOption.py ),
# then just include your script (wherever it is) here:
#
#       include("MyPackage/MySuperJobOption.py")
#
# The HWW analysis scripts are appended below, so you can see how it works!
# ==============================================================================

# # For being able to read DC14 files while already running MC15 software
# include("AthAnalysisBaseComps/ContainerRemapping.py")

# This is for the lepton fake factor analysis
hWWCommon.Global.doFakeLep = vars().get('doFakeLep', hWWCommon.Global.doFakeLep)
if hWWCommon.Global.doFakeLep:
    # Don't process FatJets (for now)
    hWWCommon.FatJets = False
    hWWCommon.FatJets.p4Systs = []
    try: from HWWFakeLeptonxAOD.HWWFakeLeptonFlags import hWWFakeLep
    except ImportError:
        hWWCommon.Global.doFakeLep = False
        hWW_msg.info("Couldn't load the lepton-fake configuration. The HWWFakeLeptonxAOD package is probably not available.")
        pass
    pass

# This is for the H->WW->lnulnu analysis
hWWCommon.Global.do2Lep = vars().get('do2Lep', hWWCommon.Global.do2Lep)
if hWWCommon.Global.do2Lep:
    # Don't process FatJets (for now)
    hWWCommon.FatJets = False
    hWWCommon.FatJets.p4Systs = []
    try: from HWWlnulnuxAODConfig.HWWlnulnuAnalysisFlags import hWWlnulnu
    except ImportError:
        hWWCommon.Global.do2Lep = False
        hWW_msg.info("Couldn't load the H->WW->lnulnu configuration. The HWWlnulnuxAODConfig package is probably not available.")
        pass
    pass

# This is for the VH, H->WW analyses
hWWCommon.Global.do3Lep = vars().get('do3Lep', hWWCommon.Global.do3Lep)
hWWCommon.Global.do4Lep = vars().get('do4Lep', hWWCommon.Global.do4Lep)
if hWWCommon.Global.do3Lep or hWWCommon.Global.do4Lep:
    # Don't process FatJets (for now)
    hWWCommon.FatJets = False
    hWWCommon.FatJets.p4Systs = []
    try: import HWWVHxAOD.WHFlags as wh_flags
    except ImportError:
        hWWCommon.Global.do3Lep = False
        hWWCommon.Global.do4Lep = False
        hWW_msg.info("Couldn't load the VH configuration. The HWWVHxAOD package is probably not available.")
        pass
    pass

# This is only for H->WW->lnuqq studies in Freiburg for now
hWWCommon.Global.do1Lep = vars().get('do1Lep', hWWCommon.Global.do1Lep)
if hWWCommon.Global.do1Lep:
    hWWCommon.Global.doORFatJets = True
    hWWCommon.Global.doORBoostedLeptons = True
    if hWWCommon.Global.do2Lep or hWWCommon.Global.do3Lep or hWWCommon.Global.do4Lep or hWWCommon.Global.doFakeLep:
        hWW_msg.warning("You asked to produce PAOD_1L AND some other PAOD. This is not allowed (due to interfernce). Will NOT produce PAOD_1L!")
        hWWCommon.Global.do1Lep = False
        pass
    else:
        try: from HWWlnuqqxAODConfig.HWWlnuqqAnalysisFlags import hWWlnuqq
        except ImportError:
            hWWCommon.Global.do1Lep = False
            hWW_msg.info("Couldn't load the H->WW->lnuqq configuration. The HWWlnuqqxAODConfig package is probably not available.")
            pass
        pass
    pass

#hWWCommon.FatJets.doWTagCut = vars().get('doWTag', hWWCommon.Global.doWTag)
hWWCommon.Global.doWTag = vars().get('doWTag', hWWCommon.Global.doWTag)

# If we want to run ONLY the efficiency and scale-factor calculations:
hWWCommon.Global.doOnlyEffiScaleFactors = vars().get('doOnlyEffiScaleFactors', hWWCommon.Global.doOnlyEffiScaleFactors)
if hWWCommon.Global.doOnlyEffiScaleFactors :
    include("PhysicsxAODConfig/HWWEfficiencyScaleFactorOnlyRun.py")
    pass

# Switch off the other outputs, if we produce the di-jet based fakes PAOD
if hWWCommon.Global.doFakeLep:
    hWW_msg.info("Running di-jet based fakes PAOD. Switching off everything else.")
    hWWCommon.Global.do2Lep = False
    hWWCommon.Global.do3Lep = False
    hWWCommon.Global.do4Lep = False
    hWWCommon.Global.do1Lep = False
    hWWCommon.Global.doP4Systematics   = False
    hWWCommon.Global.doEffiSystematics = False
    pass

# Now, actually load the wanted configurations
if hWWCommon.Global.do2Lep: include("HWWlnulnuxAODConfig/HWWlnulnuAnalysisCommon.py")
if hWWCommon.Global.do3Lep or hWWCommon.Global.do4Lep: include("HWWVHxAOD/VHAnalysisCommon.py")
if hWWCommon.Global.doFakeLep: include("HWWFakeLeptonxAOD/HWWFakeLeptonAnalysisCommon.py")
if hWWCommon.Global.do1Lep: include("HWWlnuqqxAODConfig/HWWlnuqqAnalysisCommon.py")


# ==============================================================================
#           ---- NO NEED TO CHANGE ANYTHING BELOW THIS LINE !!! ----
# ==============================================================================


from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperContainer#*")
MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperAuxContainer#*")


# # ====================================================================
# # Also add an instance of the CutFlowSvc for all other CutBookkeeperContainers
# # and add the resulting containers to all output streams/files
# # ====================================================================
# inputStreamName = af.fileinfos["stream_names"][0]
# if not hasattr(svcMgr,"CutFlowSvc"): svcMgr += CfgMgr.CutFlowSvc()
# svcMgr.CutFlowSvc.InputStream = inputStreamName
# theApp.CreateSvc += ['CutFlowSvc/CutFlowSvc']
# MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperContainer#CutBookkeepers")
# MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperAuxContainer#CutBookkeepers*")
# MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperContainer#IncompleteCutBookkeepers")
# MSMgr.AddMetaDataItemToAllStreams("xAOD::CutBookkeeperAuxContainer#IncompleteCutBookkeepers*")
# for mdItem in af.fileinfos["metadata_items"]:
#     if mdItem[0].startswith("xAOD::CutBookkeeperContainer") \
#       and not mdItem[1] == "CutBookkeepers"                 \
#       and not mdItem[1] == "IncompleteCutBookkeepers":#       \
#     #   and not mdItem[1] == "PDFSumOfWeights"                \
#     #   and not mdItem[1] == "IncompletePDFSumOfWeights" :
#         cbkName = mdItem[1]
#         hWW_msg.info("Creating now a CutFlowSvc instance for CutBookkeeperContainer with name %s" % cbkName)
#         cfsName = "CutFlowSvc"+cbkName
#         svcMgr += CfgMgr.CutFlowSvc(cfsName,
#                                     #OutputLevel              = WARNING,
#                                     InputStream              = inputStreamName,
#                                     OutputCollName           = cbkName,
#                                     OutputIncompleteCollName = "Incomplete"+cbkName
#                                     )
#         theApp.CreateSvc += [ "CutFlowSvc/"+cfsName ]
#         MSMgr.AddMetaDataItemToAllStreams( "xAOD::CutBookkeeperContainer#"+cbkName )
#         MSMgr.AddMetaDataItemToAllStreams( "xAOD::CutBookkeeperAuxContainer#"+cbkName+"*" )
#         pass
#     pass



# ====================================================================
# THINNING: We must create an instance of the ThinningSvc for all output streams.
# Thinning service name must match the one passed to the thinning tools
# ====================================================================
outputSteamNameList = []
for stream in MSMgr.StreamList:
    outputSteamNameList.append(stream.GetEventStream().name())
    pass
hWW_msg.info("Found these output stream names: %s" % outputSteamNameList)
if hWWCommon.Global.doThinning:
    from AthenaServices.Configurables import ThinningSvc
    svcMgr += ThinningSvc("HWWCommonThinning", Streams=outputSteamNameList)
    pass

# Now, actually set the list of names of output streams for the filter algorithm
if hWWCommon.Global.processReco and hasattr(hWWCommonEffiScaleFactorFilterSeq,"HWWEventDecisionAlg"):
    hWWCommonEffiScaleFactorFilterSeq.HWWEventDecisionAlg.OutputStreamNames = outputSteamNameList
    pass



# ----------------------------------------------------------------------------------------------------
# If you want to drastically reduce the information that is printed out, you can increase the general
# output level of the MessageService. The default is INFO.
# The possible options are: FATAL, ERROR, WARNING, INFO, DEBUG, VERBOSE
# ----------------------------------------------------------------------------------------------------
# rec.OutputLevel.set_Value_and_Lock( WARNING )

# Change the way Athena MultiProcessing (AthenaMP) is distribution files/events to the workers
#from AthenaMP.AthenaMPFlags import jobproperties as jps
#jps.AthenaMPFlags.Strategy = 'FileScheduling'
# 'SharedQueue' (default), 'FileScheduling', 'SharedReader' and 'TokenScatterer'
#jps.AthenaMPFlags.UseSharedReader = True
#jp.AthenaMPFlags.UseSharedWriter = True
#jps.AthenaMPFlags.CollectSubprocessLogs = True
#jps.AthenaMPFlags.WorkerTopDir = 'MPWorkers'
#jps.AthenaMPFlags.OutputReportFile = 'MPOutputs'
#jp.AthenaMPFlags.ChunkSize = 




# ==============================================================================
# Set the number of events that you want to process (-1 means all events) or skip.
# Shown is a handy way how you can use command-line options.
# If EVTMAX is not given on the command line, the default -1 (process all events) is used.
# If SKIPEVT is not given on the command line, the default 0 (start from the beginning) is used.
# This works for any command line option that you may need; it is a python feature.
# ==============================================================================
svcMgr.EventSelector.SkipEvents = vars().get('SKIPEVT', 0)
theApp.EvtMax = vars().get('EVTMAX', -1)


# Suppress warnings from unknown objects (i.e., non-xAOD objects) in the input file
#svcMgr.PoolSvc.OutputLevel=ERROR

# Change the event printout interval, if you want to
evtPrintoutInterval = vars().get('EVTPRINT', 500)
svcMgr += CfgMgr.AthenaEventLoopMgr( EventPrintoutInterval=evtPrintoutInterval )


# ==============================================================================
# Remove the long printouts of ItemListSvc at the end of the job
# ==============================================================================
# svcMgr.ItemListSvc.OutputLevel = WARNING


# ==============================================================================
# Change the maximum allowed output file sizes from 10 GB to 12 GB
# ==============================================================================
# svcMgr.AthenaPoolCnvSvc.MaxFileSizes = [ "12000000000" ]


# ==============================================================================
# Add basic code performance monitoring.
# The results will be presented at the end of your job.
# PerfMon profiles what memory was use and how long it took to run.
# Chrono tells you in an ordered table how much time was spend in each algorithm.
# ==============================================================================
from PerfMonComps.PerfMonFlags import jobproperties as pmjp
pmjp.PerfMonFlags.doFastMon = True    # to only enable a lightweight monitoring

if vars().get('doChrono',True):
    svcMgr.AuditorSvc += CfgMgr.ChronoAuditor() #monitor calls to functions in components
    theApp.AuditAlgorithms = True #enable auditors for algorithms
    svcMgr.ChronoStatSvc.NumberOfSkippedEventsForMemStat = 10
    svcMgr.ChronoStatSvc.PrintUserTime     = False
    svcMgr.ChronoStatSvc.PrintSystemTime   = False
    svcMgr.ChronoStatSvc.PrintEllapsedTime = False  #If True, show the wall clock time
    svcMgr.AthenaEventLoopMgr.UseDetailChronoStat = True
    svcMgr.AthenaPoolCnvSvc.UseDetailChronoStat   = True #show details about I/O performance
    pass


# ==============================================================================
# Optional include to suppress as much athena output as possible
# ==============================================================================
# include("AthAnalysisBaseComps/SuppressLogging.py")
# Copy it here and allow ChronoStatSvc to print summary
#needs to happen at end of joboptions
# svcMgr.MessageSvc.OutputLevel=WARNING
# if hasattr(svcMgr,"PoolSvc") : svcMgr.PoolSvc.OutputLevel=ERROR #even stricter for PoolSvc! Fixme: maybe just add to setError below?
# svcMgr.MessageSvc.setInfo = Configurable.allConfigurables.keys()
# svcMgr.MessageSvc.setError = ["HistogramPersistencySvc"] #even stricter for HistogramPersistencySvc too .. gives a silly/harmless warning otherwise
# excludeList = ['CoreDumpSvc','TopAlg', 'DataModelCompatSvc', 'EventSelector',
#                'MetaDataSvc', #'ChronoStatSvc',
#                'AthDictLoaderSvc', #'AuditorSvc',
#                'ClassIDSvc', 'AthOutSeq', 'RndmGenSvc', 'InputMetaDataStore',
#                'StatusCodeSvc', 'AthMasterSeq', 'AthenaRootStreamerSvc',
#                'AthRegSeq', 'IOVDbMetaDataTool', 'Streams', 'ProxyProviderSvc',
#                'AlgContextAuditor', 'NTupleSvc', 'AthenaPoolCnvSvc',
#                'EventPersistencySvc', 'AthenaSealSvc', 'IncidentSvc', 'PoolSvc',
#                'ApplicationMgr', 'MetaDataStore', 'ServiceManager',
#                'AthenaPoolAddressProviderSvc', 'HistogramDataSvc', 'HistoryStore']
# for x in excludeList :
#     while x in svcMgr.MessageSvc.setInfo : svcMgr.MessageSvc.setInfo.remove(x)
#     pass


# ==============================================================================
# Change the basket size only for the DataHeaderForm in order to increase the
# efficiency of the compression
# ==============================================================================
# from HWWlnulnuxAODConfig.HWWlnulnuAnalysisFlags import hWWlnulnu
# svcMgr.AthenaPoolCnvSvc.PoolAttributes += [ "ContainerName = 'POOLContainerForm(DataHeaderForm)'; BRANCH_BASKET_SIZE = '50000000'" ] # 10 MB
# svcMgr.AthenaPoolCnvSvc.PoolAttributes += [ "DatabaseName = '" + hWWlnulnu.Global.FileName + "'; ContainerName = 'TTree=POOLContainerForm'; CONTAINER_SPLITLEVEL = '99'" ]
# svcMgr.AthenaPoolCnvSvc.PoolAttributes += [ "DatabaseName = '" + hWWlnulnu.Global.FileName + "'; COMPRESSION_LEVEL = '9'" ]
# svcMgr.AthenaPoolCnvSvc.PoolAttributes += [ "ContainerName = 'POOLContainerForm(DataHeaderForm)'; BRANCH_BASKET_SIZE = '2000000'" ] # 2 MB


# Some more stuff if you want to profile a given algorithm using valgrind
# For more info, see: https://twiki.cern.ch/twiki/bin/view/AtlasComputing/OptimisingCode
# svcMgr += CfgMgr.ValgrindSvc( OutputLevel        = VERBOSE,
#                               IgnoreFirstNEvents = 5,
#                               ProfiledAlgs       = [ "HWWMuonCalibrationSmearingAlg",
#                                                      "HWWMuonSelectionAlg",
#                                                      "HWWMuonEffiScaleFactorAlg" ] )
# Run it with:
# valgrind --tool=callgrind --trace-children=yes --num-callers=8 --collect-jumps=yes --instr-atstart=no `which athena.py` --stdcmalloc HWWAnalysis_topOptions.py
