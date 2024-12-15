##=============================================================================
## Name:        HWWlnuqqAnalysisFlags.py
##
## Author:      Karsten Koeneke
## Created:     December 2015
##
## Description: Here, all neccessary job flags for the Higgs->WW->lnuqq analysis
##              are defined.
##=============================================================================

__doc__ = """Here, all neccessary job flags for the Higgs->WW->lnuqq analysis are defined."""
__version__ = "0.0.1"
__author__  = "Karsten Koeneke <karsten.koeneke@cern.ch>"

from AthenaCommon.JobProperties import JobProperty, JobPropertyContainer
from AthenaCommon.JobProperties import jobproperties

# Import the module that allows to use named units, e.g. GeV
from AthenaCommon.SystemOfUnits import *

# Import the common steering flags for this analysis
#from PhysicsxAODConfig.HWWCommonAnalysisFlags import hWWCommon
import PhysicsxAODConfig.HWWCommonAnalysisFlags as hWWCommonFlags
from PhysicsxAODConfig.HWWCommonAnalysisFlags import hWWCommon


#=====================================================================
# First define container for the flags
#=====================================================================
class HWWlnuqqAnalysisFlags(JobPropertyContainer):
    """ The Higgs->WW->lnuqq analysis flag/job property container."""
jobproperties.add_Container(HWWlnuqqAnalysisFlags)

#short-cut to get the HiggsWWlnuqqAnalysisFlags container with this one line:
#'from HWWlnuqqxAODConfig.HWWlnuqqAnalysisFlags import hWWlnuqq'
#Note that name has to be different to avoid problems with pickle
hWWlnuqq = jobproperties.HWWlnuqqAnalysisFlags



#=====================================================================
# Now define each flag and add it to the container
#=====================================================================

class Global(hWWCommonFlags.Global):
    """
    Global steering for the H->WW->lnuqq analysis.
    The common parts are directly taken from PhysicsxAODConfig/python/HWWCommonFlags.py.
    """
    statusOn         = True
    allowedTypes     = ['bool']
    StoredValue      = True
    DPDMakerScript   = "HWWlnuqqxAODConfig/HWWlnuqqAnalysisCommon.py"
    writePxAOD       = True
    StreamName       = "PAOD_1L"
    FileName         = "PAOD_1L.pool.root"
    writePxAODMETCut = False
    METStreamName    = "PAOD_1LMET"
    METFileName      = "PAOD_1LMET.pool.root"
    minMETCut        = 60.0*GeV
    doSkimming       = True
    acceptAlgList    = [] # This is a default. It will be filled during the job setup
    requireAlgList   = [] # This is a default. It will be filled during the job setup
    pass
hWWlnuqq.add_JobProperty(Global)


class Event(JobProperty):
    """
    Event steering for the H->WW->lnuqq analysis.
    """
    statusOn            = True
    allowedTypes        = ['bool']
    StoredValue         = True
    ejjEvent            = "EventEjetjet"
    mjjEvent            = "EventMjetjet"
    eJEvent             = "EventEJET"
    mJEvent             = "EventMJET"
    eJEventDrSorted     = "EventEJET_DRsorted"
    mJEventDrSorted     = "EventMJET_DRsorted"
    vbfLeadJetPtMin     = 40.0*GeV
    vbfJetJetMassMin    = 600.0*GeV
    vbfJetJetDeltaYMin  = 3.0
    hadWLeadJetPtMin    = 80.0*GeV
    hadWJetAbsEtaMax    = 2.4
    hadWJetJetMassMin   = 45.0*GeV
    hadWJetJetMassMax   = 250.0*GeV
    resolvedLeptonPtMin = 30.0*GeV
    pass
hWWlnuqq.add_JobProperty(Event)




class FatJets(hWWCommonFlags.FatJets):
    """Definitions for the large-R jets for the H->WW->lvJ analysis"""
    statusOn              = True
    allowedTypes          = ['bool']
    StoredValue           = True
    # And now the final selection (on top of the selection done in hWWCommonFlags.FatJets)
    cutMassMin            = 20*GeV
    pass
hWWlnuqq.add_JobProperty(FatJets)



# Let's actually overwrite some kinematic cuts from the common flags file:
# https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/HiggsPhys/Run2/HWW/HWWxAODCode/HWWCommonxAODConfig/trunk/python/HWWCommonAnalysisFlags.py
# We can do that in this exceptional case since the PAOD_1L will be produced in
# a separate job from a separate DAOD, compared to all the other outputs.

# Trigger (use only single-lepton triggers)
#hWWCommon.Trigger.diMuonTriggerList       = []
#hWWCommon.Trigger.diElectronTriggerList   = []
#hWWCommon.Trigger.electronMuonTriggerList = []
#hWWCommon.Trigger.diLeptonTriggerList     = []
#hWWCommon.Trigger.allLeptonTriggerList    = hWWCommon.Trigger.singleLeptonTriggerList

# Electrons
hWWCommon.Electrons.preSelection.cutPtMin = 7.0*GeV
hWWCommon.Electrons.cutPtMin              = 25.0*GeV
# Availability in HIGG5D2
hWWCommon.Electrons.isoWorkingPointList = [
    "FCLoose", "FCTight", "HighPtCaloOnly", "Gradient", "PLVLoose", "PLVTight",
    "Gradient_exp",
    "TightTrackOnly_VarRad", "TightTrackOnly_FixedRad", "Tight_VarRad", "Loose_VarRad"
]

# Muons
hWWCommon.Muons.preSelection.cutPtMin     = 7.0*GeV
hWWCommon.Muons.cutPtMin                  = 20.0*GeV

# Jets
hWWCommon.Jets.preSelection.cutPtMinList  = [30.0*GeV]
