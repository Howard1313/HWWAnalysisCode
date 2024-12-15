#See: https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/SoftwareTutorialxAODAnalysisInCMake for more details about anything here

#testFile = '/afs/cern.ch/work/y/yunju/private/XAODAna/ROOTAnalysis/DAOD_PHYS.21569875._001323.pool.root.1'
#testFile = '/afs/cern.ch/work/y/yunju/private/Boost/TruthXAOD/xAODAna/samples/DAOD_TRUTH3.341452mumuWWlvqq.pool.root'
#testFile = '/eos/user/y/yunju/BoostSamples/sharetruth3/DAOD_TRUTH3.346560.PowhegPythia8_WmH125J_MINLO_lvWWlvqq.root'
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/DAOD_TRUTH3.341452.PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_mumuWWlvqq_VpT.root'
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/DAOD_TRUTH3.341450.PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_eeWWlvqq_VpT.root'

#Zee(341450)
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/user.yunju.yjt3_1_EXT0/user.yunju.29022765.EXT0._000001.DAOD_TRUTH3.test.pool.root'
#Zmuu(341452)
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/user.yunju.yjt3_2_341452_EXT0/user.yunju.29022766.EXT0._000001.DAOD_TRUTH3.test.pool.root'
#W+
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/user.yunju.yjt3_346561_1_EXT0/user.yunju.29022775.EXT0._000001.DAOD_TRUTH3.test.pool.root'
#W-
#testFile ='/eos/user/y/yunju/BoostSamples/sharetruth3/user.yunju.yjt3_346560_1_EXT0/user.yunju.29022767.EXT0._000001.DAOD_TRUTH3.test.pool.root'

#qqZuu(341452)
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_qqZmumu/DAOD_HIGG5D2.27420870._000010.pool.root.1"
#ggZuu(601409)
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_ggZmumu/DAOD_HIGG5D2.30570143._000001.pool.root.1"
testFile ="/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_ggZmumu/mc16_13TeV.601409.PhPy8EG_A14NNPDF23_ggZmumuHlvqq.deriv.DAOD_HIGG5D2.e8412_s3126_r9364_p4310/merge.root"
#ggZee(601408)
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_ggZee/mc16_13TeV.601408.PhPy8EG_A14NNPDF23_ggZeeHlvqq.deriv.DAOD_HIGG5D2.e8412_e7400_s3126_r9364_r9315_p4310/merge.root"
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_ggZee/mc16_13TeV.601408.PhPy8EG_A14NNPDF23_ggZeeHlvqq.deriv.DAOD_HIGG5D2.e8412_e7400_s3126_r9364_r9315_p4310/DAOD_HIGG5D2.30570124._000001.pool.root.1" 

#testFile ='/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_qqZee/merge_file.root'
#testFile ='/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_qqZmumu/merge_file.root'
#testFile ='/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_W_plus_H/merge_file.root'
#testFile ='/eos/user/l/lihao/lvqq_truth_samples/lvqq_truth_W_minus_H/merge_file.root'

#Zjet mumu(364100)
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/Zjets_364100/mc16_13TeV.364100.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_HIGG5D2.e5271_e5984_s3126_r10724_r10726_p4308/DAOD_HIGG5D2.24508824._000001.pool.root.1"
#Wjets(364156)
#testFile ="/eos/user/l/lihao/lvqq_truth_samples/Wjets_364156/mc16_13TeV/DAOD_HIGG5D2.22961037._000001.pool.root.1"
#Single Top(410646)
#testFile = "/eos/user/l/lihao/lvqq_truth_samples/top_410646/mc16_13TeV/DAOD_HIGG5D2.22955320._000001.pool.root.1"
#multi-boson(364254)
#testFile = "/eos/user/l/lihao/lvqq_truth_samples/diBoson_364254/mc16_13TeV/DAOD_HIGG5D2.22954916._000001.pool.root.1"

#override next line on command line with: --filesInput=XXX
jps.AthenaCommonFlags.FilesInput = [testFile]

#Specify AccessMode (read mode) ... ClassAccess is good default for xAOD
jps.AthenaCommonFlags.AccessMode = "ClassAccess"


jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:WmHMyxAODAnalysis.outputs.root"]
svcMgr.THistSvc.MaxFileSize=-1

# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )

# later on we'll add some configuration options for our algorithm that go here

# Add our algorithm to the main alg sequence
athAlgSeq += alg
# limit the number of events (for testing purposes)
#theApp.EvtMax = 500
theApp.EvtMax = -1

# optional include for reducing printout from athena
include("AthAnalysisBaseComps/SuppressLogging.py")