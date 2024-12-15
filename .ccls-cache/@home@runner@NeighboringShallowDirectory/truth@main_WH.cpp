#include "PMGTools/PMGTruthWeightTool.h"
#include "xAODJet/JetContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include <AsgMessaging/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>

MyxAODAnalysis ::MyxAODAnalysis(const std::string &name,
                                ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.
}

StatusCode MyxAODAnalysis ::initialize() {
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  ANA_CHECK(book(TH1F("Boson_pdgid", "Boson_pdgid", 30, 0, 30)));
  ANA_CHECK(book(TH1F("BosonD_pdgid", "BosonD_pdgid", 30, 0, 30)));
  ANA_CHECK(book(TH1F("n_HBoson", "n_HBoson", 16, 0, 16)));
  ANA_CHECK(book(TH1F("n_qdW", "n_qdW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_edW", "n_edW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_udW", "n_udW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_tdW", "n_tdW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_ldW", "n_ldW", 11, 0, 11)));

  ANA_CHECK(book(TH1F("n_HWde", "n_HWde", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdve", "n_HWdve", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdu", "n_HWdu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdvu", "n_HWdvu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdt", "n_HWdt", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdvt", "n_HWdvt", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdcl", "n_HWdcl", 11, 0, 11)));

  ANA_CHECK(book(TH1F("n_HParent", "n_HParent", 11, 0, 11)));
  ANA_CHECK(book(TH1F("HP_nParent", "HP_nParent", 11, 0, 11)));
  ANA_CHECK(book(TH1F("HP_nChild", "HP_nChild", 11, 0, 11)));

  ANA_CHECK(book(TH1F("H_status", "H_status", 190, 0, 190)));
  ANA_CHECK(book(TH1F("VW_status", "VW_status", 190, 0, 190)));
  ANA_CHECK(book(TH1F("H_pt", "H_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VW_pt", "VW_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("dpt_WH_scalar", "dpt_WH_scalar[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("sumpt_WH_vector", "sumpt_WH_vector[GeV]", 50, 0, 500)));
  
  ANA_CHECK(book(TH1F("Hparent_pdgid", "Hparent_pdgid", 60, -30, 30)));

  ANA_CHECK(book(TH1F("n_VWde", "n_VWde", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdve", "n_VWdve", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdu", "n_VWdu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdvu", "n_VWdvu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdt", "n_VWdt", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdvt", "n_VWdvt", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWdcl", "n_VWdcl", 11, 0, 11)));
  
  ANA_CHECK(book(TH1F("njet", "njet", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_100", "njet_100", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_200", "njet_200", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_300", "njet_300", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_400", "njet_400", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nSRjet", "nSRjet", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon", "nmuon", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon_p", "nmuon_p", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon_m", "nmuon_m", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele", "nele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele_p", "nele_p", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele_m", "nele_m", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nlep", "nlep", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HW", "n_HW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_ldHW", "n_ldHW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_ldVW", "n_ldVW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWele", "n_HWele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWele", "n_VWele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWmuon", "n_HWmuon", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWmuon", "n_VWmuon", 11, 0, 11)));
  ANA_CHECK(book(TH1F("HWde_pt", "HWde_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VWde_pt", "VWde_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("HWdu_pt", "HWdu_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VWdu_pt", "VWdu_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("HWdcl_pt", "HWdcl_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VWdcl_pt", "VWdcl_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("ntau", "ntau", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWtau", "n_HWtau", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWtau", "n_VWtau", 11, 0, 11)));

  ANA_CHECK(book(TH1F("Vlep_pt>Hlep_pt", "Vlep_pt>Hlep_pt", 3, 0, 3)));

  ANA_CHECK(book(TH1F("n_HWtaude", "n_HWtaude", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWtaudu", "n_HWtaudu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWtaude", "n_VWtaude", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWtaudu", "n_VWtaudu", 11, 0, 11)));
  
  ANA_CHECK(book(TH1F("n_HWtd_ele", "n_HWtd_ele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWtd_muon", "n_HWtd_muon", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWtd_ele", "n_VWtd_ele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_VWtd_muon", "n_VWtd_muon", 11, 0, 11)));

  ANA_CHECK(book(TH1F("HWele_pt", "HWele_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VWele_pt", "VWele_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("HWtd_ele_pt", "HWtd_ele_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("VWtd_ele_pt", "VWtd_ele_pt[GeV]", 50, 0, 500)));

  ANA_CHECK(book(TH1F("dR_HWele_HW", "dR_HWele_HW", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWele_VW", "dR_VWele_VW", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWtd_ele_HW", "dR_HWtd_ele_HW", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWtd_ele_VW", "dR_VWtd_ele_VW", 25, 0,5)));
  

  ANA_CHECK(book(TH1F("dR_VW_jet1_2u0e", "dR_VW_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_jet1_2u0e", "dR_HW_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_qdW_jet1_2u0e", "dR_qdW_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1qdW_jet1_2u0e", "dR_jet1qdW_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_VW_2u0e", "dR_HW_VW_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_lep1_lep2_2u0e", "dR_lep1_lep2_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_VWdcl_2u0e", "dR_HWdcl_VWdcl_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_jet1_2u0e", "dR_VWdcl_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_lep1_2u0e", "dR_VWdcl_lep1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_lep2_2u0e", "dR_VWdcl_lep2_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_jet1_2u0e", "dR_HWdcl_jet1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_lep1_2u0e", "dR_HWdcl_lep1_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_lep2_2u0e", "dR_HWdcl_lep2_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_Rclep_2u0e", "dR_VWdcl_Rclep_2u0e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_Rclep_2u0e", "dR_HWdcl_Rclep_2u0e", 25, 0,5)));
   

  ANA_CHECK(book(TH1F("dR_VW_jet1_1u1e", "dR_VW_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_jet1_1u1e", "dR_HW_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_qdW_jet1_1u1e", "dR_qdW_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1qdW_jet1_1u1e", "dR_jet1qdW_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_VW_1u1e", "dR_HW_VW_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_lep1_lep2_1u1e", "dR_lep1_lep2_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_VWdcl_1u1e", "dR_HWdcl_VWdcl_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_jet1_1u1e", "dR_VWdcl_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_lep1_1u1e", "dR_VWdcl_lep1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_lep2_1u1e", "dR_VWdcl_lep2_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_jet1_1u1e", "dR_HWdcl_jet1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_lep1_1u1e", "dR_HWdcl_lep1_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_lep2_1u1e", "dR_HWdcl_lep2_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VWdcl_Rclep_1u1e", "dR_VWdcl_Rclep_1u1e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HWdcl_Rclep_1u1e", "dR_HWdcl_Rclep_1u1e", 25, 0,5)));
  
  ANA_CHECK(book(TH1F("dR_VW_Rcjet1_2u1j", "dR_VW_Rcjet1_2u1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_Rcjet1_2u1j", "dR_HW_Rcjet1_2u1j", 25, 0,5)));

  ANA_CHECK(book(TH1F("dR_VW_RcSRjet1_2u1j", "dR_VW_RcSRjet1_2u1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_RcSRjet2_2u1j", "dR_VW_RcSRjet2_2u1j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet1_2u1j", "dR_HW_RcSRjet1_2u1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet2_2u1j", "dR_HW_RcSRjet2_2u1j", 25, 0,5))); 
  /////////////////////////
  ANA_CHECK(book(TH1F("dR_VW_Rcjet1_2u2j", "dR_VW_Rcjet1_2u2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_Rcjet2_2u2j", "dR_VW_Rcjet2_2u2j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_Rcjet1_2u2j", "dR_HW_Rcjet1_2u2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_Rcjet2_2u2j", "dR_HW_Rcjet2_2u2j", 25, 0,5))); 

  ANA_CHECK(book(TH1F("dR_VW_RcSRjet1_2u2j", "dR_VW_RcSRjet1_2u2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_RcSRjet2_2u2j", "dR_VW_RcSRjet2_2u2j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet1_2u2j", "dR_HW_RcSRjet1_2u2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet2_2u2j", "dR_HW_RcSRjet2_2u2j", 25, 0,5))); 
  /////////////////////////
  ANA_CHECK(book(TH1F("dR_VW_Rcjet1_1u1e1j", "dR_VW_Rcjet1_1u1e1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_Rcjet1_1u1e1j", "dR_HW_Rcjet1_1u1e1j", 25, 0,5)));

  ANA_CHECK(book(TH1F("dR_VW_RcSRjet1_1u1e1j", "dR_VW_RcSRjet1_1u1e1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_RcSRjet2_1u1e1j", "dR_VW_RcSRjet2_1u1e1j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet1_1u1e1j", "dR_HW_RcSRjet1_1u1e1j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet2_1u1e1j", "dR_HW_RcSRjet2_1u1e1j", 25, 0,5))); 
  /////////////////////////
  ANA_CHECK(book(TH1F("dR_VW_Rcjet1_1u1e2j", "dR_VW_Rcjet1_1u1e2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_Rcjet2_1u1e2j", "dR_VW_Rcjet2_1u1e2j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_Rcjet1_1u1e2j", "dR_HW_Rcjet1_1u1e2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_Rcjet2_1u1e2j", "dR_HW_Rcjet2_1u1e2j", 25, 0,5))); 

  ANA_CHECK(book(TH1F("dR_VW_RcSRjet1_1u1e2j", "dR_VW_RcSRjet1_1u1e2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_VW_RcSRjet2_1u1e2j", "dR_VW_RcSRjet2_1u1e2j", 25, 0,5))); 
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet1_1u1e2j", "dR_HW_RcSRjet1_1u1e2j", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_HW_RcSRjet2_1u1e2j", "dR_HW_RcSRjet2_1u1e2j", 25, 0,5))); 



  ANA_CHECK(book(TH1F("MET", "MET[GeV]", 50, 0, 500)));

  // ANA_CHECK(book(TH1F("VW_pt", "VW_pt[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("H_pt", "H_pt[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("dpt_HW", "dpt_HW[GeV]", 50, -500, 500)));
  // ANA_CHECK(book(TH1F("WH_pt", "WH_pt[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("dPt_met_vl", "dPt_met_vl[GeV]", 50, -500, 500)));
  ANA_CHECK(book(TH1F("sumET", "sumET[GeV]", 50, 0, 500)));

  
  
  ANA_CHECK(book(TH1F("dP3_Hjet_qdW", "dP3_Hjet_qdW[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("dP3_Hjet1_Hjet2", "dP3_Hjet1_Hjet2[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("dP3_Hjet2_qdW", "dP3_Hjet2_qdW[GeV]", 50, 0, 500)));

  

  ANA_CHECK(book(TH1F("SumPx_lep_jet", "SumPx_lep_jet[GeV]", 100, -500, 500)));
  ANA_CHECK(book(TH1F("SumPy_lep_jet", "SumPy_lep_jet[GeV]", 100, -500, 500)));
  ANA_CHECK(book(TH1F("SumPx_lep_SRjet", "SumPx_lep_SRjet[GeV]", 100, -500, 500)));
  ANA_CHECK(book(TH1F("SumPy_lep_SRjet", "SumPy_lep_SRjet[GeV]", 100, -500, 500)));



  return StatusCode::SUCCESS;
}

StatusCode MyxAODAnalysis ::execute() {
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(evtStore()->retrieve(eventInfo, "EventInfo"));

  float weight = 0;
  // //retrive event weight
  // ToolHandle<PMGTools::IPMGTruthWeightTool> m_weightTool;
  // m_weightTool.setTypeAndName("PMGTools::PMGTruthWeightTool/PMGTruthWeightTool");
  // ATH_CHECK(m_weightTool.retrieve());

  // int n_weight = 0;

  // ANA_MSG_INFO("weight:"<<weight);
  // for (auto weight_name : m_weightTool->getWeightNames()) {
  // n_weight++;
  // weight = m_weightTool->getWeight(weight_name);
  // ANA_MSG_INFO("weight_name:"<<weight_name<<" weight:"<<weight);
  // //my_histogram_map[weight].Fill(my_variable,
  // m_weightTool->getWeight(weight));
  // }
  // ANA_MSG_INFO("n_weight: "<<n_weight);
  // hist("n_weight")->Fill(n_weight);
  // hist("weight")->Fill(weight);
  weight = 1;

  // print out run and event number from retrieved object
  std::cout << "================= start" << std::endl;
  ANA_MSG_INFO("================= in execute, runNumber = "
               << eventInfo->runNumber()
               << ", eventNumber = " << eventInfo->eventNumber());

  

  const xAOD::JetContainer *truthak10jet(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthak10jet,
                                 "AntiKt10TruthTrimmedPtFrac5SmallR20Jets"));
  ANA_MSG_INFO("retrieve fatjet successfully");

  const xAOD::JetContainer* truthak4jet(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthak4jet, "AntiKt4TruthDressedWZJets"));

  

  int qqZuu_flag = 1;
  const xAOD::TruthParticleContainer *truthBosonD(nullptr);
  const xAOD::TruthParticleContainer *truthBoson(nullptr);
  if (qqZuu_flag == 0) {
    ATH_CHECK(evtStore()->retrieve(truthBosonD, "TruthBosonsWithDecayParticles"));
  }

  if (qqZuu_flag == 1) {
    ATH_CHECK(evtStore()->retrieve(truthBosonD, "TruthWbosonWithDecayParticles"));
    ATH_CHECK(evtStore()->retrieve(truthBoson, "TruthBoson"));
  }

  ANA_MSG_INFO("retrieve BosonD successfully");

  std::vector<const xAOD::TruthParticle*> vec_HBoson;
  std::vector<const xAOD::TruthParticle*> vec_HParent;
  std::vector<const xAOD::TruthParticle*> vec_HW;
  std::vector<const xAOD::TruthParticle*> vec_qdW;
  std::vector<const xAOD::TruthParticle*> vec_edW;
  std::vector<const xAOD::TruthParticle*> vec_udW;
  std::vector<const xAOD::TruthParticle*> vec_tdW;
  std::vector<const xAOD::TruthParticle*> vec_ldW;
  
  if (qqZuu_flag == 1) {
    for (std::size_t i = 0; i < truthBoson->size(); ++i) {
      auto ithBoson = truthBoson->at(i);
      hist("Boson_pdgid")->Fill(abs(ithBoson->pdgId()), weight);
      
      if (abs(ithBoson->pdgId()) == 25) {
        if (ithBoson->nParents() == 0) vec_HBoson.push_back(ithBoson);
        if (ithBoson->nParents() > 0) if (abs(ithBoson->parent(0)->pdgId()) != 25) {
          vec_HBoson.push_back(ithBoson);
          for (std::size_t i = 0; i < ithBoson->nParents(); ++i){
            vec_HParent.push_back(ithBoson->parent(i));
            hist("Hparent_pdgid")->Fill(ithBoson->parent(i)->pdgId(), weight);
          }
        }
      }
      if (abs(ithBoson->pdgId()) == 25 && ithBoson->nChildren() == 2) {
        auto child1 = ithBoson->child(0);
        auto child2 = ithBoson->child(1);
        if (child1->absPdgId()==24) vec_HW.push_back(child1);
        if (child1->nChildren()>0) if (child1->child(0)->absPdgId()==24) vec_HW.push_back(child1->child(0));
        if (child2->absPdgId()==24) vec_HW.push_back(child2);
        if (child2->nChildren()>0) if (child2->child(0)->absPdgId()==24) vec_HW.push_back(child2->child(0));
      }
    }
    ANA_MSG_INFO("for loop Boson successfully");
  }

  for (std::size_t i = 0; i < truthBosonD->size(); ++i) {
    auto ithBoson = truthBosonD->at(i);
    hist("BosonD_pdgid")->Fill(abs(ithBoson->pdgId()), weight);
    
    // if (abs(ithBoson->pdgId()) == 24) {
      //hist("W_n_parent")->Fill(ithBoson->nParents(), weight);
      //hist("W_n_child")->Fill(ithBoson->nChildren(), weight);
      // if (ithBoson->nParents() > 0)
        //hist("W_parent_pdgid")->Fill(abs(ithBoson->parent(0)->pdgId()), weight);
      // if (ithBoson->nChildren() == 1){
        //hist("W_child_pdgid")->Fill(abs(ithBoson->child(0)->pdgId()), weight);
      // }
    // }
    
    if (abs(ithBoson->pdgId()) == 24 && ithBoson->nChildren() == 2) {
      auto child1 = ithBoson->child(0);
      auto child2 = ithBoson->child(1);
      if (abs(child1->pdgId()) < 6 && abs(child2->pdgId()) < 6) vec_qdW.push_back(ithBoson);
    }
    
    if (abs(ithBoson->pdgId()) == 24 && ithBoson->nChildren() >0) {
      for (std::size_t i = 0; i < ithBoson->nChildren(); ++i) {
        auto child = ithBoson->child(i);
        if (abs(child->pdgId())== 11) {
          vec_edW.push_back(ithBoson);
          vec_ldW.push_back(ithBoson);
        }
        if (abs(child->pdgId())== 13) {
          vec_udW.push_back(ithBoson);
          vec_ldW.push_back(ithBoson);
        }
        if (abs(child->pdgId())== 15) {
          vec_tdW.push_back(ithBoson);
          vec_ldW.push_back(ithBoson);
        }
      }  
    }

    if (abs(ithBoson->pdgId()) == 25) {
      if (ithBoson->nParents() == 0) vec_HBoson.push_back(ithBoson);
      if (ithBoson->nParents() > 0) if (abs(ithBoson->parent(0)->pdgId()) != 25) vec_HBoson.push_back(ithBoson);
    }

   if (abs(ithBoson->pdgId()) == 25 && ithBoson->nChildren() == 2) {
      auto child1 = ithBoson->child(0);
      auto child2 = ithBoson->child(1);
      if (child1->absPdgId()==24) vec_HW.push_back(child1);
      if (child1->nChildren()>0) if (child1->child(0)->absPdgId()==24) vec_HW.push_back(child1->child(0));
      if (child2->absPdgId()==24) vec_HW.push_back(child2);
      if (child2->nChildren()>0) if (child2->child(0)->absPdgId()==24) vec_HW.push_back(child2->child(0));
    }
  }
  ANA_MSG_INFO("for loop BosonD successfully");

  int n_HBoson = vec_HBoson.size(); hist("n_HBoson")->Fill(n_HBoson, weight);
  int n_qdW = vec_qdW.size(); hist("n_qdW")->Fill(n_qdW, weight);
  int n_edW = vec_edW.size(); hist("n_edW")->Fill(n_edW, weight);
  int n_udW = vec_udW.size(); hist("n_udW")->Fill(n_udW, weight);
  int n_tdW = vec_tdW.size(); hist("n_tdW")->Fill(n_tdW, weight);
  int n_ldW = vec_ldW.size(); hist("n_ldW")->Fill(n_ldW, weight);
  int n_HW = vec_HW.size(); hist("n_HW")->Fill(n_HW, weight);

 

  // HBoson
  const xAOD::TruthParticle* H_Tpart= vec_HBoson.at(0);

  // std::cout<<"\n\n"<<"H_descender_tree";
  // auto H_descender_tree = get_descender_tree(H_Tpart);

  // std::cout<<"\n\n"<<"qdW_descender_tree";
  // auto qdW_descender_tree = get_descender_tree(vec_qdW.at(0));
  // std::cout<<"\n\n"<<"qdW_ancestor_tree";
  // auto qdW_ancestor_tree = get_ancestor_tree(vec_qdW.at(0));

  // lepton decay HW
  std::vector<const xAOD::TruthParticle*> vec_ldHW;
  for (int i = 0; i < n_ldW; ++i){
    auto ldW=vec_ldW.at(i);
    for (int i = 0; i < n_HW; ++i){
      int HW_barcode =vec_HW.at(i)->barcode();
      if (ldW->barcode()==HW_barcode) vec_ldHW.push_back(ldW);                            
    }
  }
  int n_ldHW = vec_ldHW.size(); hist("n_ldHW")->Fill(n_ldHW, weight);
  // lepton decay VW
  std::vector<const xAOD::TruthParticle*> vec_ldVW;
  if(n_ldHW==1){
    int ldHW_barcode =vec_ldHW.at(0)->barcode();
    for (int i = 0; i < n_ldW; ++i){
      auto ldW=vec_ldW.at(i);
      if (ldW->barcode()!=ldHW_barcode) vec_ldVW.push_back(ldW);
    }
  }
  int n_ldVW = vec_ldVW.size(); hist("n_ldVW")->Fill(n_ldVW, weight);
  //find HW,VW
  // std::vector<const xAOD::TruthParticle*> vec_ldW_qdWdR(vec_ldW);
  // auto cmp_Tpart_qdWdR = [vec_qdW](const xAOD::TruthParticle* a, const xAOD::TruthParticle* b) -> bool
  // { 
  //   return a->p4().DeltaR(vec_qdW.at(0)->p4()) < b->p4().DeltaR(vec_qdW.at(0)->p4());
  // };
  // std::sort(vec_ldW_qdWdR.begin(), vec_ldW_qdWdR.end(),cmp_Tpart_qdWdR);
  
  const xAOD::TruthParticle* HW_Tpart= vec_ldHW.at(0);
  const xAOD::TruthParticle* VW_Tpart= vec_ldVW.at(0);

  hist("H_status")->Fill(H_Tpart->status(), weight);
  hist("H_pt")->Fill(H_Tpart->pt()/1000, weight);
  hist("VW_status")->Fill(VW_Tpart->status(), weight);
  hist("VW_pt")->Fill(VW_Tpart->pt()/1000, weight);
  hist("dpt_WH_scalar")->Fill((VW_Tpart->pt()-H_Tpart->pt())/1000, weight);
  hist("sumpt_WH_vector")->Fill((VW_Tpart->p4()+H_Tpart->p4()).Pt()/1000, weight);

  
  // if(vec_HParent.size()>0) {
  //   hist("n_HParent")->Fill(vec_HParent.size(), weight);
  //   hist("HP_nParent")->Fill(vec_HParent.at(0)->nParents(), weight);
  //   hist("HP_nChild")->Fill(vec_HParent.at(0)->nChildren(), weight);
  //   std::cout<<"\n\n"<<"HParent_ancestor_tree";
  //   auto a = get_ancestor_tree(vec_HParent.at(0));
  //   std::cout<<"\n\n"<<"HParent_descender_tree";
  //   auto b = get_descender_tree(vec_HParent.at(0));
  // }



  // std::cout<<"\n\n"<<"VW_descender_tree";
  // auto VW_descender_tree = get_descender_tree(VW_Tpart);
  // std::cout<<"\n\n"<<"VW_ancestor_tree";
  // auto VW_ancestor_tree = get_ancestor_tree(VW_Tpart);
  // std::cout<<"\n\n"<<"HW_descender_tree";
  // auto HW_descender_tree = get_descender_tree(HW_Tpart);
  // std::cout<<"\n\n"<<"HW_ancestor_tree";
  // auto HW_ancestor_tree = get_ancestor_tree(HW_Tpart);
  
  std::vector<const xAOD::TruthParticle*> vec_HWde;
  std::vector<const xAOD::TruthParticle*> vec_HWdve;
  std::vector<const xAOD::TruthParticle*> vec_HWdu;
  std::vector<const xAOD::TruthParticle*> vec_HWdvu;
  std::vector<const xAOD::TruthParticle*> vec_HWdt;
  std::vector<const xAOD::TruthParticle*> vec_HWdvt;
  
  for (std::size_t i = 0; i < HW_Tpart->nChildren(); ++i) {
    auto child = HW_Tpart->child(i);
    if(child->absPdgId()==11) vec_HWde.push_back(child);
    if(child->absPdgId()==12) vec_HWdve.push_back(child);
    if(child->absPdgId()==13) vec_HWdu.push_back(child);
    if(child->absPdgId()==14) vec_HWdvu.push_back(child);
    if(child->absPdgId()==15) vec_HWdt.push_back(child);
    if(child->absPdgId()==16) vec_HWdvt.push_back(child);
  }

  int n_HWde = vec_HWde.size(); hist("n_HWde")->Fill(n_HWde, weight);
  int n_HWdve = vec_HWdve.size(); hist("n_HWdve")->Fill(n_HWdve, weight);
  int n_HWdu = vec_HWdu.size(); hist("n_HWdu")->Fill(n_HWdu, weight);
  int n_HWdvu = vec_HWdvu.size(); hist("n_HWdvu")->Fill(n_HWdvu, weight);
  int n_HWdt = vec_HWdt.size(); hist("n_HWdt")->Fill(n_HWdt, weight);
  int n_HWdvt = vec_HWdvt.size(); hist("n_HWdvt")->Fill(n_HWdvt, weight);

  std::vector<const xAOD::TruthParticle*> vec_HWdcl(vec_HWde);
  vec_HWdcl.insert(vec_HWdcl.end(), vec_HWdu.begin(), vec_HWdu.end());
  int n_HWdcl = vec_HWdcl.size();hist("n_HWdcl")->Fill(n_HWdcl, weight);

  std::vector<const xAOD::TruthParticle*> vec_VWde;
  std::vector<const xAOD::TruthParticle*> vec_VWdve;
  std::vector<const xAOD::TruthParticle*> vec_VWdu;
  std::vector<const xAOD::TruthParticle*> vec_VWdvu;
  std::vector<const xAOD::TruthParticle*> vec_VWdt;
  std::vector<const xAOD::TruthParticle*> vec_VWdvt;
  
  for (std::size_t i = 0; i < VW_Tpart->nChildren(); ++i) {
    auto child = VW_Tpart->child(i);
    if(child->absPdgId()==11) vec_VWde.push_back(child);
    if(child->absPdgId()==12) vec_VWdve.push_back(child);
    if(child->absPdgId()==13) vec_VWdu.push_back(child);
    if(child->absPdgId()==14) vec_VWdvu.push_back(child);
    if(child->absPdgId()==15) vec_VWdt.push_back(child);
    if(child->absPdgId()==16) vec_VWdvt.push_back(child);
  }

  int n_VWde = vec_VWde.size(); hist("n_VWde")->Fill(n_VWde, weight);
  int n_VWdve = vec_VWdve.size(); hist("n_VWdve")->Fill(n_VWdve, weight);
  int n_VWdu = vec_VWdu.size(); hist("n_VWdu")->Fill(n_VWdu, weight);
  int n_VWdvu = vec_VWdvu.size(); hist("n_VWdvu")->Fill(n_VWdvu, weight);
  int n_VWdt = vec_VWdt.size(); hist("n_VWdt")->Fill(n_VWdt, weight);
  int n_VWdvt = vec_VWdvt.size(); hist("n_VWdvt")->Fill(n_VWdvt, weight);

  std::vector<const xAOD::TruthParticle*> vec_VWdcl(vec_VWde);
  vec_VWdcl.insert(vec_VWdcl.end(), vec_VWdu.begin(), vec_VWdu.end());
  int n_VWdcl = vec_VWdcl.size();hist("n_VWdcl")->Fill(n_VWdcl, weight);

  
  
  //Wdeu,Wdveu,l=e,u,t
  // std::vector<const xAOD::TruthParticle*> vec_HWdeu(vec_HWde);
  // vec_HWdeu.insert(vec_HWdeu.end(), vec_HWdu.begin(), vec_HWdu.end());
  // std::vector<const xAOD::TruthParticle*> vec_VWdeu(vec_VWde);
  // vec_VWdeu.insert(vec_VWdeu.end(), vec_VWdu.begin(), vec_VWdu.end());


  float SumPx_lep_jet=0;
  float SumPx_lep_SRjet=0;
  float SumPy_lep_jet=0;
  float SumPy_lep_SRjet=0;
  //met
  const xAOD::MissingETContainer *MET_Truth(nullptr);
  ATH_CHECK(evtStore()->retrieve(MET_Truth, "MET_Truth"));
  ANA_MSG_INFO("retrieve MET successfully");
  
  const xAOD::MissingET *METCand = MET_Truth->at(0);
  TLorentzVector MET_TLV(METCand->mpx(),METCand->mpy(),0,METCand->met());
  hist("sumET")->Fill(METCand->sumet()/1000, weight);

  // construct vecjet
  std::vector<TLorentzVector> vecjet;
  for (std::size_t i = 0; i < truthak10jet->size(); ++i) {
    auto jet = truthak10jet->at(i);
    if(jet->pt()/1000>200) vecjet.push_back(jet->p4());
    //vecjet.push_back(jet->p4());
    TLorentzVector jet_TLV=jet->p4();
    // SumPx_lep_jet+=jet_TLV.Px();
    // SumPy_lep_jet+=jet_TLV.Py();
  }
  std::sort(vecjet.begin(), vecjet.end(), cmp_pt);
  int njet=vecjet.size(); hist("njet")->Fill(njet, weight);
  
  // construct vecEle
  const xAOD::TruthParticleContainer *truthElectrons(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthElectrons, "TruthElectrons"));
  ANA_MSG_INFO("retrieve electron successfully");

  std::vector<const xAOD::TruthParticle*> vecele;
  std::vector<const xAOD::TruthParticle*> vecele_p;
  std::vector<const xAOD::TruthParticle*> vecele_m;
  for (std::size_t i = 0; i < truthElectrons->size(); ++i) {
    auto ele = truthElectrons->at(i);
    if(ele->pt()/1000>5){
      vecele.push_back(ele);
      if (ele->pdgId() == -11) vecele_p.push_back(ele);
      if (ele->pdgId() == 11) vecele_m.push_back(ele);
    }
    TLorentzVector ele_TLV=ele->p4();
    SumPx_lep_jet+=ele_TLV.Px();
    SumPy_lep_jet+=ele_TLV.Py();
    SumPx_lep_SRjet+=ele_TLV.Px();
    SumPy_lep_SRjet+=ele_TLV.Py();
  }
  std::sort(vecele.begin(), vecele.end(), cmp_pt);
  
  // construct vecmuon
  const xAOD::TruthParticleContainer *truthMuons(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthMuons, "TruthMuons"));
  ANA_MSG_INFO("retrieve muon successfully");
  
  std::vector<const xAOD::TruthParticle*> vecmuon;
  std::vector<const xAOD::TruthParticle*> vecmuon_p;
  std::vector<const xAOD::TruthParticle*> vecmuon_m;
  

  for (std::size_t i = 0; i < truthMuons->size(); ++i) {
    auto muon = truthMuons->at(i);
    if(muon->pt()/1000>5){
      vecmuon.push_back(muon);
      if (muon->pdgId() == -13) vecmuon_p.push_back(muon);
      if (muon->pdgId() == 13) vecmuon_m.push_back(muon);
    }
    
    
    // auto origin_pdgid=get_origin_pdgid(muon);
    // if(origin_pdgid==25) vec_Horigin_muon.push_back(muon);
    // if(abs(origin_pdgid)==24) vec_Worigin_muon.push_back(muon);
    // if(abs(origin_pdgid)==15) vec_tau_muon.push_back(muon);
    // if(abs(origin_pdgid)==5) vec_bquark_muon.push_back(muon);

    TLorentzVector muon_TLV=muon->p4();
    SumPx_lep_jet+=muon_TLV.Px();
    SumPy_lep_jet+=muon_TLV.Py();
    SumPx_lep_SRjet+=muon_TLV.Px();
    SumPy_lep_SRjet+=muon_TLV.Py();
  }
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt);
  std::sort(vecmuon_p.begin(), vecmuon_p.end(), cmp_pt);
  std::sort(vecmuon_m.begin(), vecmuon_m.end(), cmp_pt);


  
  // construct veclep
  std::vector<const xAOD::TruthParticle*> veclep(vecmuon);
  veclep.insert(veclep.end(), vecele.begin(), vecele.end());
  // std::sort(veclep.begin(), veclep.end(), cmp_pt);

  if(njet>=1){
    auto cmp_jet1_dR = [vecjet](const xAOD::TruthParticle* a, const xAOD::TruthParticle* b) -> bool
    { 
      return a->p4().DeltaR(vecjet.at(0)) > b->p4().DeltaR(vecjet.at(0));
    };
    std::sort(veclep.begin(), veclep.end(), cmp_jet1_dR );
  }
  
  
  
  int nmuon = vecmuon.size();  hist("nmuon")->Fill(nmuon, weight);
  int nmuon_p = vecmuon_p.size(); hist("nmuon_p")->Fill(nmuon_p, weight);
  int nmuon_m = vecmuon_m.size(); hist("nmuon_m")->Fill(nmuon_m, weight);
  int nele = vecele.size(); hist("nele")->Fill(nele, weight);
  int nele_p = vecele_p.size(); hist("nele_p")->Fill(nele_p, weight);
  int nele_m = vecele_m.size(); hist("nele_m")->Fill(nele_m, weight);
  int nlep = veclep.size(); hist("nlep")->Fill(nlep, weight); 

  std::vector<const xAOD::TruthParticle*> vec_HWele;
  for (int i = 0; i < n_HWde; ++i){
    int HWde_barcode = vec_HWde.at(i)->barcode();
    int HW_barcode = HW_Tpart->barcode();
    for (int i = 0; i < nele; ++i){
      auto ele=vecele.at(i);
      if (ele->barcode()==HWde_barcode) {vec_HWele.push_back(ele);}
      else if (ele->nParents()>0) {if (ele->parent(0)->barcode()==HW_barcode) vec_HWele.push_back(ele);}
    }
  }
  std::vector<const xAOD::TruthParticle*> vec_VWele;
  for (int i = 0; i < n_VWde; ++i){
    int VWde_barcode =vec_VWde.at(i)->barcode();
    int VW_barcode = VW_Tpart->barcode();
    for (int i = 0; i < nele; ++i){
      auto ele=vecele.at(i);
      if (ele->barcode()==VWde_barcode) {vec_VWele.push_back(ele);}
      else if (ele->nParents()>0) {if (ele->parent(0)->barcode()==VW_barcode) vec_VWele.push_back(ele);}
    }
  }
  std::vector<const xAOD::TruthParticle*> vec_HWmuon;
  for (int i = 0; i < n_HWdu; ++i){
    int HWdu_barcode =vec_HWdu.at(i)->barcode();
    int HW_barcode = HW_Tpart->barcode();
    for (int i = 0; i < nmuon; ++i){
      auto muon=vecmuon.at(i);
      if (muon->barcode()==HWdu_barcode) {vec_HWmuon.push_back(muon);}
      else if (muon->nParents()>0) {if (muon->parent(0)->barcode()==HW_barcode) vec_HWmuon.push_back(muon);}
    }
  }
  std::vector<const xAOD::TruthParticle*> vec_VWmuon;
  for (int i = 0; i < n_VWdu; ++i){
    int VWdu_barcode =vec_VWdu.at(i)->barcode();
    int VW_barcode = VW_Tpart->barcode();
    for (int i = 0; i < nmuon; ++i){
      auto muon=vecmuon.at(i);
      if (muon->barcode()==VWdu_barcode) {vec_VWmuon.push_back(muon);}
      else if (muon->nParents()>0) {if (muon->parent(0)->barcode()==VW_barcode) vec_VWmuon.push_back(muon);}
    }
  }

  int n_HWele = vec_HWele.size(); hist("n_HWele")->Fill(n_HWele, weight);
  int n_VWele = vec_VWele.size(); hist("n_VWele")->Fill(n_VWele, weight);
  int n_HWmuon = vec_HWmuon.size(); hist("n_HWmuon")->Fill(n_HWmuon, weight); 
  int n_VWmuon = vec_VWmuon.size(); hist("n_VWmuon")->Fill(n_VWmuon, weight); 

  //find Hlep
  // auto cmp_HWde_dP3 = [vec_HWde](const xAOD::TruthParticle* a, const xAOD::TruthParticle* b) -> bool
  // { 
  //   return (a->p4()-vec_HWde.at(0)->p4()).Vect().Mag() < (b->p4()-vec_HWde.at(0)->p4()).Vect().Mag();
  // };
  // if(n_HWde>0 && n_HWele>1) std::sort(vec_HWele.begin(), vec_HWele.end(),cmp_HWde_dP3);


  if(n_HWde>0)  hist("HWde_pt")->Fill(vec_HWde.at(0)->pt()/1000, weight);
  if(n_VWde>0)  hist("VWde_pt")->Fill(vec_VWde.at(0)->pt()/1000, weight);
  if(n_HWdu>0)  hist("HWdu_pt")->Fill(vec_HWdu.at(0)->pt()/1000, weight);
  if(n_VWdu>0)  hist("VWdu_pt")->Fill(vec_VWdu.at(0)->pt()/1000, weight);
  if(n_HWdcl>0 && n_VWdcl>0)  {
    hist("HWdcl_pt")->Fill(vec_HWdcl.at(0)->pt()/1000, weight);
    hist("VWdcl_pt")->Fill(vec_VWdcl.at(0)->pt()/1000, weight);

    int VlepPT_LargerThan_HlepPT=0;
    if(vec_VWdcl.at(0)->pt()>vec_HWdcl.at(0)->pt()) VlepPT_LargerThan_HlepPT=1;
    hist("Vlep_pt>Hlep_pt")->Fill(VlepPT_LargerThan_HlepPT, weight);
  }  

  if(nele>2){
    std::cout<<"ele/n";
    for (int i = 0; i < nele; ++i) auto a = get_ancestor_tree(vecele.at(i));
  }

  const xAOD::TruthParticleContainer *truthTaus(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthTaus, "TruthTaus"));
  
  std::vector<const xAOD::TruthParticle*> vectau;
  for (std::size_t i = 0; i < truthTaus->size(); ++i) {
    auto tau = truthTaus->at(i);
    if(tau->pt()/1000>5){
      vectau.push_back(tau);
    }
  }
  int ntau=vectau.size();hist("ntau")->Fill(ntau, weight);

  std::vector<const xAOD::TruthParticle*> vec_HWtau;
  for (int i = 0; i < n_HWdt; ++i){
    int HWdt_barcode = vec_HWdt.at(i)->barcode();
    int HW_barcode = HW_Tpart->barcode();
    for (int i = 0; i < ntau; ++i){
      auto tau=vectau.at(i);
      if (tau->barcode()==HWdt_barcode) {vec_HWtau.push_back(tau);}
      else if (tau->nParents()>0) {if (tau->parent(0)->barcode()==HW_barcode) vec_HWtau.push_back(tau);}
    }
  }
  std::vector<const xAOD::TruthParticle*> vec_VWtau;
  for (int i = 0; i < n_VWdt; ++i){
    int VWdt_barcode =vec_VWdt.at(i)->barcode();
    int VW_barcode = VW_Tpart->barcode();
    for (int i = 0; i < ntau; ++i){
      auto tau=vectau.at(i);
      if (tau->barcode()==VWdt_barcode) {vec_VWtau.push_back(tau);}
      else if (tau->nParents()>0) {if (tau->parent(0)->barcode()==VW_barcode) vec_VWtau.push_back(tau);}
    }
  }
  int n_HWtau = vec_HWtau.size(); hist("n_HWtau")->Fill(n_HWtau, weight);
  int n_VWtau = vec_VWtau.size(); hist("n_VWtau")->Fill(n_VWtau, weight);

  std::vector<const xAOD::TruthParticle*> vec_HWtaude;
  std::vector<const xAOD::TruthParticle*> vec_HWtaudu;
  if(n_HWtau==1) {
    for (std::size_t i = 0; i < vec_HWtau.at(0)->nChildren(); ++i) {
      auto child = vec_HWtau.at(0)->child(i);
      if(child->absPdgId()==11) vec_HWtaude.push_back(child);
      if(child->absPdgId()==13) vec_HWtaudu.push_back(child);
    }
  } 

  std::vector<const xAOD::TruthParticle*> vec_VWtaude;
  std::vector<const xAOD::TruthParticle*> vec_VWtaudu;
  if(n_VWtau==1) {
    for (std::size_t i = 0; i < vec_VWtau.at(0)->nChildren(); ++i) {
      auto child = vec_VWtau.at(0)->child(i);
      if(child->absPdgId()==11) vec_VWtaude.push_back(child);
      if(child->absPdgId()==13) vec_VWtaudu.push_back(child);
    }
  } 
  int n_HWtaude = vec_HWtaude.size(); hist("n_HWtaude")->Fill(n_HWtaude, weight);
  int n_HWtaudu = vec_HWtaudu.size(); hist("n_HWtaudu")->Fill(n_HWtaudu, weight);
  int n_VWtaude = vec_VWtaude.size(); hist("n_VWtaude")->Fill(n_VWtaude, weight);
  int n_VWtaudu = vec_VWtaudu.size(); hist("n_VWtaudu")->Fill(n_VWtaudu, weight);

  std::vector<const xAOD::TruthParticle*> vec_HWtd_ele;
  std::vector<const xAOD::TruthParticle*> vec_HWtd_muon;
  std::vector<const xAOD::TruthParticle*> vec_VWtd_ele;
  std::vector<const xAOD::TruthParticle*> vec_VWtd_muon;
  if(n_HWtau>0){
    for (int i = 0; i < n_HWtaude; ++i){
      int HWtaude_barcode =vec_HWtaude.at(i)->barcode();
      int HWtau_barcode = vec_HWtau.at(0)->barcode();
      for (int i = 0; i < nele; ++i){
        auto ele=vecele.at(i);
        if (ele->barcode()==HWtaude_barcode) {vec_HWtd_ele.push_back(ele);}
        else if (ele->nParents()>0) {if (ele->parent(0)->barcode()==HWtau_barcode) vec_HWtd_ele.push_back(ele);}
      }
    }
    for (int i = 0; i < n_HWtaudu; ++i){
      int HWtaudu_barcode =vec_HWtaudu.at(i)->barcode();
      int HWtau_barcode = vec_HWtau.at(0)->barcode();
      for (int i = 0; i < nmuon; ++i){
        auto muon=vecmuon.at(i);
        if (muon->barcode()==HWtaudu_barcode) {vec_HWtd_muon.push_back(muon);}
        else if (muon->nParents()>0) {if (muon->parent(0)->barcode()==HWtau_barcode) vec_HWtd_muon.push_back(muon);}
      }
    }
  }
  int n_HWtd_ele = vec_HWtd_ele.size(); hist("n_HWtd_ele")->Fill(n_HWtd_ele, weight);
  int n_HWtd_muon = vec_HWtd_muon.size(); hist("n_HWtd_muon")->Fill(n_HWtd_muon, weight);
  
  if(n_VWtau>0){
    for (int i = 0; i < n_VWtaude; ++i){
      int VWtaude_barcode =vec_VWtaude.at(i)->barcode();
      int VWtau_barcode = vec_VWtau.at(0)->barcode();
      for (int i = 0; i < nele; ++i){
        auto ele=vecele.at(i);
        if (ele->barcode()==VWtaude_barcode) {vec_VWtd_ele.push_back(ele);}
        else if (ele->nParents()>0) {if (ele->parent(0)->barcode()==VWtau_barcode) vec_VWtd_ele.push_back(ele);}
      }
    }
    for (int i = 0; i < n_VWtaudu; ++i){
      int VWtaudu_barcode =vec_VWtaudu.at(i)->barcode();
      int VWtau_barcode = vec_VWtau.at(0)->barcode();
      for (int i = 0; i < nmuon; ++i){
        auto muon=vecmuon.at(i);
        if (muon->barcode()==VWtaudu_barcode) {vec_VWtd_muon.push_back(muon);}
        else if (muon->nParents()>0) {if (muon->parent(0)->barcode()==VWtau_barcode) vec_VWtd_muon.push_back(muon);}
      }
    }
  }
  int n_VWtd_ele = vec_VWtd_ele.size(); hist("n_VWtd_ele")->Fill(n_VWtd_ele, weight);
  int n_VWtd_muon = vec_VWtd_muon.size(); hist("n_VWtd_muon")->Fill(n_VWtd_muon, weight);

  if(n_HWele>0) {
    auto HWele=vec_HWele.at(0);
    hist("HWele_pt")->Fill(HWele->pt()/1000, weight);
    hist("dR_HWele_HW")->Fill(HWele->p4().DeltaR(HW_Tpart->p4()), weight);
  }
  if(n_VWele>0) {
    auto VWele=vec_VWele.at(0);
    hist("VWele_pt")->Fill(VWele->pt()/1000, weight);
    hist("dR_VWele_VW")->Fill(VWele->p4().DeltaR(VW_Tpart->p4()), weight);
  }
  if(n_HWtd_ele>0) {
    auto HWtd_ele=vec_HWtd_ele.at(0);
    hist("HWtd_ele_pt")->Fill(HWtd_ele->pt()/1000, weight);
    hist("dR_HWtd_ele_HW")->Fill(HWtd_ele->p4().DeltaR(HW_Tpart->p4()), weight);
  }
  if(n_VWtd_ele>0) {
    auto VWtd_ele=vec_VWtd_ele.at(0);
    hist("VWtd_ele_pt")->Fill(VWtd_ele->pt()/1000, weight);
    hist("dR_VWtd_ele_VW")->Fill(VWtd_ele->p4().DeltaR(VW_Tpart->p4()), weight);
  }

  // for (int i = 0; i < n_HWdt; ++i) {
  //    std::cout<<"HWdt"<<i<<"/n";
  //    auto a = get_ancestor_tree(vec_HWdt.at(i));
  //    auto b = get_descender_tree(vec_HWdt.at(i));
  // }
  // for (int i = 0; i < ntau; ++i) {
  //    std::cout<<"tau"<<i<<"/n";
  //    auto a = get_ancestor_tree(vectau.at(i));
  //    auto b = get_descender_tree(vectau.at(i));
  // }


  float H_pt=H_Tpart->pt()/1000;
  if (H_pt <100){
    hist("njet_100")->Fill(njet, weight);
  }
  if (H_pt >100 && H_pt <200){
    hist("njet_200")->Fill(njet, weight);
  }
  if (H_pt >200 && H_pt <300){
    hist("njet_300")->Fill(njet, weight);
  }
  if (H_pt >300){
    hist("njet_400")->Fill(njet, weight);
  }


  

  //dR jet VW
  std::vector<TLorentzVector> vecjet_VWdR(vecjet);
  auto cmp_TLV_VWdR = [VW_Tpart](TLorentzVector& a, TLorentzVector& b) -> bool
  { 
    return a.DeltaR(VW_Tpart->p4())< b.DeltaR(VW_Tpart->p4());
  };
  std::sort(vecjet_VWdR.begin(), vecjet_VWdR.end(),cmp_TLV_VWdR);
  
   
  //dR jet HW
  std::vector<TLorentzVector> vecjet_HWdR(vecjet);
  auto cmp_TLV_HWdR = [HW_Tpart](TLorentzVector& a, TLorentzVector& b) -> bool
  { 
    return a.DeltaR(HW_Tpart->p4())< b.DeltaR(HW_Tpart->p4());
  };
  std::sort(vecjet_HWdR.begin(), vecjet_HWdR.end(),cmp_TLV_HWdR);

  //dR jet HW
  std::vector<TLorentzVector> vecjet_qdWdR(vecjet);
  auto cmp_TLV_qdWdR = [vec_qdW](TLorentzVector& a, TLorentzVector& b) -> bool
  { 
    return a.DeltaR(vec_qdW.at(0)->p4())< b.DeltaR(vec_qdW.at(0)->p4());
  };
  std::sort(vecjet_qdWdR.begin(), vecjet_qdWdR.end(),cmp_TLV_qdWdR);



  //construct vecSRjet
  std::vector<TLorentzVector> vecSRjet;
  for (std::size_t i = 0; i < truthak4jet->size(); ++i) {
    auto SRjet = truthak4jet->at(i);
    vecSRjet.push_back(SRjet->p4());
    // TLorentzVector SRjet_TLV=SRjet->p4();
    // SumPx_lep_SRjet+=SRjet_TLV.Px();
    // SumPy_lep_SRjet+=SRjet_TLV.Py();
  }
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_pt);
  int nSRjet = vecSRjet.size(); hist("nSRjet")->Fill(nSRjet, weight);

  //dR SRjet VW
  std::vector<TLorentzVector> vecSRjet_VWdR(vecSRjet);
  std::sort(vecSRjet_VWdR.begin(), vecSRjet_VWdR.end(),cmp_TLV_VWdR);
  
   
  //dR SRjet HW
  std::vector<TLorentzVector> vecSRjet_HWdR(vecSRjet);
  std::sort(vecSRjet_HWdR.begin(), vecSRjet_HWdR.end(),cmp_TLV_HWdR);
  
  

  // // construct vectau
  // std::vector<TLorentzVector> vectau;
  // std::vector<TLorentzVector> vectau_p;
  // std::vector<TLorentzVector> vectau_m;
  // std::vector<TLorentzVector> vec_tdeu;
  // for (std::size_t i = 0; i < truthTaus->size(); ++i) {
  //   auto tau = truthTaus->at(i);
  //   vectau.push_back(tau->p4());
  //   if (tau->pdgId() == -15) vectau_p.push_back(tau->p4());
  //   if (tau->pdgId() == 15) vectau_m.push_back(tau->p4());
  //   hist("tau_n_child")->Fill(tau->nChildren(), weight);
  //   for (std::size_t i = 0; i < tau->nChildren(); ++i) {
  //     auto child=tau->child(i);
  //     hist("tau_child_pdgid")->Fill(child->pdgId(), weight);
  //     if(abs(child->pdgId())==11 || abs(child->pdgId())==13) {
  //       vec_tdeu.push_back(child->p4());
  //       hist("dP3_tau_EUchild")->Fill((tau->p4()-child->p4()).Vect().Mag()/1000, weight);
  //       hist("dR_tau_EUchild")->Fill(tau->p4().DeltaR(child->p4()), weight);
  //       hist("dPt_tau_EUchild")->Fill((tau->p4()-child->p4()).Pt()/1000, weight);
  //     }
  //     if(tau->nChildren()==4) hist("4Ctau_child_pdgid")->Fill(child->pdgId(), weight);
  //     if(tau->nChildren()==3) hist("3Ctau_child_pdgid")->Fill(child->pdgId(), weight);
  //     if(tau->nChildren()==2) hist("2Ctau_child_pdgid")->Fill(child->pdgId(), weight);
  //     if(tau->nChildren()==1) hist("1Ctau_child_pdgid")->Fill(child->pdgId(), weight);
  //   }
  // }
  // std::sort(vectau.begin(), vectau.end(), cmp_pt);
  // int ntau = vectau.size();
  // int ntau_p = vectau_p.size();
  // int ntau_m = vectau_m.size();
  // int n_tdeu = vec_tdeu.size();
  // hist("n_tdeu")->Fill(n_tdeu, weight);

  // // construct vec_Wdeu_tdeu
  // std::vector<TLorentzVector> vec_Wdeutdeu(vec_Wde);
  // vec_Wdeutdeu.insert(vec_Wdeutdeu.end(), vec_Wdu.begin(), vec_Wdu.end());
  // vec_Wdeutdeu.insert(vec_Wdeutdeu.end(), vec_tdeu.begin(), vec_tdeu.end());
  // int n_Wdeutdeu = vec_Wdeutdeu.size();
  // hist("n_Wdeutdeu")->Fill(n_Wdeutdeu, weight);
  
  // std::vector<TLorentzVector> vec_Wdeutdeu_HWdR(vec_Wdeutdeu);
  // std::sort(vec_Wdeutdeu_HWdR.begin(), vec_Wdeutdeu_HWdR.end(), cmp_HWdR);
  // if(n_Wdeutdeu>=1 && n_ldW>=1)hist("dR_Wdeutdeu1_HW")->Fill(vec_Wdeutdeu_HWdR.at(0).DeltaR(vec_ldW_qdWdR.at(0)), weight);
  
  // std::vector<TLorentzVector> vec_Wdeutdeu_VWdR(vec_Wdeutdeu);
  // std::sort(vec_Wdeutdeu_VWdR.begin(), vec_Wdeutdeu_VWdR.end(), cmp_VWdR);
  // if(n_Wdeutdeu>=1 && n_ldW>=2)hist("dR_Wdeutdeu1_VW")->Fill(vec_Wdeutdeu_VWdR.at(0).DeltaR(vec_ldW_qdWdR.at(1)), weight);

  
  

  
  
  // float Zmass = 91187.6; // MeV
  // float Hmass = 125250;  // MeV
  // float Wmass = 80433;   // MeV

  
  // // find Hjet
  // std::vector<TLorentzVector> vecHjet(vecjet);
  // auto cmp_qdW_dP3 = [vec_qdW](TLorentzVector& a, TLorentzVector& b) -> bool
  // { 
  //   return (a-vec_qdW.at(0)).Vect().Mag() < (b-vec_qdW.at(0)).Vect().Mag();
  // };
  // std::sort(vecHjet.begin(), vecHjet.end(),cmp_qdW_dP3);
  // int njet = vecjet.size();
  // if(njet>=1) hist("dP3_Hjet_qdW")->Fill((vecHjet.at(0)-vec_qdW.at(0)).Vect().Mag()/1000, weight);
  // if(njet>=2) hist("dP3_Hjet1_Hjet2")->Fill((vecHjet.at(0)-vecHjet.at(1)).Vect().Mag()/1000, weight);
  // if(njet>=2) hist("dP3_Hjet2_qdW")->Fill((vecHjet.at(1)-vec_qdW.at(0)).Vect().Mag()/1000, weight);

  
  
  // SumPx_lep_jet+=MET_TLV.Px();
  // SumPy_lep_jet+=MET_TLV.Py();
  // SumPx_lep_SRjet+=MET_TLV.Px();
  // SumPy_lep_SRjet+=MET_TLV.Py();

  // hist("SumPx_lep_jet")->Fill(SumPx_lep_jet * 0.001, weight);
  // hist("SumPy_lep_jet")->Fill(SumPy_lep_jet * 0.001, weight);
  // hist("SumPx_lep_SRjet")->Fill(SumPx_lep_SRjet * 0.001, weight);
  // hist("SumPy_lep_SRjet")->Fill(SumPy_lep_SRjet * 0.001, weight);

  // std::cout << "nmuon: " << nmuon << std::endl;
  // std::cout << "nele: " << nele   << std::endl;
  // std::cout << "nak10jet: " << njet << std::endl;


  // // W mT
  // // float W_mT_Hmuon = 9999999;
  // // if (nHmuon >= 1) {
  // //   auto ET_lep =sqrt(Hmuon_TLV.M() * Hmuon_TLV.M() + Hmuon_TLV.Pt() * Hmuon_TLV.Pt());
  // //   auto dPhi_l_miss = fabs(Hmuon_TLV.Phi() - METCand->phi());
  // //   if (dPhi_l_miss >= TMath::Pi()) dPhi_l_miss = 2 * TMath::Pi() - dPhi_l_miss;
  // //   W_mT_Hmuon = sqrt(2 * ET_lep * METCand->met() * (1 - cos(dPhi_l_miss)));
  // // }
  
  // // selection
  // std::set<int> selection_passed;
  // selection_passed.insert(0);
  // // selection 1
  // if (nlep >= 1) {
  //   if (veclep.at(0).Pt() > 27000) selection_passed.insert(1);
  // }
  // // //selection 2
  // if (nmuon >= 1) {
  //   if (abs(vecmuon.at(0).Eta()) < 2.5) selection_passed.insert(2);
  // }
  // if (nele >= 1) {
  //   float ele1_eta = vecele.at(0).Eta();
  //   if (abs(ele1_eta) < 1.37 || (abs(ele1_eta) > 1.52 && abs(ele1_eta) < 2.47)) selection_passed.insert(2);
  // }

  // //selection 3
  // if (njet >= 1) {
  //   if (vecjet.at(0).M() > 40000) selection_passed.insert(3);
  // }

  // //selection 4
  // if (nmuon == 2 && njet == 1) selection_passed.insert(4);

  // //selection 5
  // if (nmuon == 2 && njet == 2) selection_passed.insert(5);

  // //selection 6
  // if (nmuon == 1 && nele == 1 && njet == 1) selection_passed.insert(6);

  // //selection 7
  // if (nmuon == 1 && nele == 1 && njet == 2) selection_passed.insert(7);

  // //selection 8
  // if (njet == 1) selection_passed.insert(8);

  // //selection 9
  // if (njet == 2) selection_passed.insert(9);

  if (n_HWdu == 1 &&  n_VWdu == 1 && njet == 1){
    hist("dR_VW_Rcjet1_2u1j")->Fill(vecjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet1_2u1j")->Fill(vecjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_VW_RcSRjet1_2u1j")->Fill(vecSRjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_VW_RcSRjet2_2u1j")->Fill(vecSRjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_HW_RcSRjet1_2u1j")->Fill(vecSRjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_HW_RcSRjet2_2u1j")->Fill(vecSRjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
  }

  if (n_HWdu == 1 &&  n_VWdu == 1 && njet == 2){
    hist("dR_VW_Rcjet1_2u2j")->Fill(vecjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_VW_Rcjet2_2u2j")->Fill(vecjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet1_2u2j")->Fill(vecjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet2_2u2j")->Fill(vecjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_VW_RcSRjet1_2u2j")->Fill(vecSRjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_VW_RcSRjet2_2u2j")->Fill(vecSRjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_HW_RcSRjet1_2u2j")->Fill(vecSRjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_HW_RcSRjet2_2u2j")->Fill(vecSRjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
  }

  if (n_HWdu == 1 &&  n_VWde == 1 && njet == 1){
    hist("dR_VW_Rcjet1_1u1e1j")->Fill(vecjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet1_1u1e1j")->Fill(vecjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_VW_RcSRjet1_1u1e1j")->Fill(vecSRjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_VW_RcSRjet2_1u1e1j")->Fill(vecSRjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_HW_RcSRjet1_1u1e1j")->Fill(vecSRjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_HW_RcSRjet2_1u1e1j")->Fill(vecSRjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
  }

  if (n_HWdu == 1 &&  n_VWde == 1 && njet == 2){
    hist("dR_VW_Rcjet1_1u1e2j")->Fill(vecjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_VW_Rcjet2_1u1e2j")->Fill(vecjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet1_1u1e2j")->Fill(vecjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    hist("dR_HW_Rcjet2_1u1e2j")->Fill(vecjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_VW_RcSRjet1_1u1e2j")->Fill(vecSRjet_VWdR.at(0).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_VW_RcSRjet2_1u1e2j")->Fill(vecSRjet_VWdR.at(1).DeltaR(VW_Tpart->p4()), weight);
    if(nSRjet>=1) hist("dR_HW_RcSRjet1_1u1e2j")->Fill(vecSRjet_HWdR.at(0).DeltaR(HW_Tpart->p4()), weight);
    if(nSRjet>=2) hist("dR_HW_RcSRjet2_1u1e2j")->Fill(vecSRjet_HWdR.at(1).DeltaR(HW_Tpart->p4()), weight);
  }

  if (njet >= 1){
    if(nmuon==2 && nele==0){
      hist("dR_VW_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(VW_Tpart->p4()), weight);
      hist("dR_HW_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(HW_Tpart->p4()), weight);
      hist("dR_HW_VW_2u0e")->Fill(VW_Tpart->p4().DeltaR(HW_Tpart->p4()), weight);
      hist("dR_lep1_lep2_2u0e")->Fill(veclep.at(0)->p4().DeltaR(veclep.at(1)->p4()), weight);
      if(n_HWdcl>=1 && n_VWdcl>=1) {
        hist("dR_VWdcl_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_lep1_2u0e")->Fill(veclep.at(0)->p4().DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_lep2_2u0e")->Fill(veclep.at(1)->p4().DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_lep1_2u0e")->Fill(veclep.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_lep2_2u0e")->Fill(veclep.at(1)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_VWdcl_2u0e")->Fill(vec_VWdcl.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_Rclep_2u0e")->Fill(std::min(veclep.at(0)->p4().DeltaR(vec_VWdcl.at(0)->p4()),veclep.at(1)->p4().DeltaR(vec_VWdcl.at(0)->p4())), weight);
        hist("dR_HWdcl_Rclep_2u0e")->Fill(std::min(veclep.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()),veclep.at(1)->p4().DeltaR(vec_HWdcl.at(0)->p4())), weight);
        hist("dR_qdW_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(vec_qdW.at(0)->p4()), weight);
        hist("dR_jet1qdW_jet1_2u0e")->Fill(vecjet.at(0).DeltaR(vecjet_qdWdR.at(0)), weight);
      }
    }
    if(nmuon==1 && nele==1){
      hist("dR_VW_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(VW_Tpart->p4()), weight);
      hist("dR_HW_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(HW_Tpart->p4()), weight);
      hist("dR_HW_VW_1u1e")->Fill(VW_Tpart->p4().DeltaR(HW_Tpart->p4()), weight);
      hist("dR_lep1_lep2_1u1e")->Fill(veclep.at(0)->p4().DeltaR(veclep.at(1)->p4()), weight);
      if(n_HWdcl>=1 && n_VWdcl>=1) {
        hist("dR_VWdcl_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_lep1_1u1e")->Fill(veclep.at(0)->p4().DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_lep2_1u1e")->Fill(veclep.at(1)->p4().DeltaR(vec_VWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_lep1_1u1e")->Fill(veclep.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_lep2_1u1e")->Fill(veclep.at(1)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_HWdcl_VWdcl_1u1e")->Fill(vec_VWdcl.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()), weight);
        hist("dR_VWdcl_Rclep_1u1e")->Fill(std::min(veclep.at(0)->p4().DeltaR(vec_VWdcl.at(0)->p4()),veclep.at(1)->p4().DeltaR(vec_VWdcl.at(0)->p4())), weight);
        hist("dR_HWdcl_Rclep_1u1e")->Fill(std::min(veclep.at(0)->p4().DeltaR(vec_HWdcl.at(0)->p4()),veclep.at(1)->p4().DeltaR(vec_HWdcl.at(0)->p4())), weight);
        hist("dR_qdW_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(vec_qdW.at(0)->p4()), weight);
        hist("dR_jet1qdW_jet1_1u1e")->Fill(vecjet.at(0).DeltaR(vecjet_qdWdR.at(0)), weight);
      }
    }
  }

  


  // //selection_used{0,4,6};//(1u1e1j)
  // std::set<int> selection_used{0,8};


  // // // std::includes(selection_passed.begin(), selection_passed.end(),
  // // // selection_used.begin(), selection_used.end())
  // if (std::includes(selection_passed.begin(), selection_passed.end(),
  //                   selection_used.begin(), selection_used.end())) {
  // }
  ANA_MSG_INFO("construct selection done");
  std::cout << "end event----------------------" << std::endl;
  return StatusCode::SUCCESS;
}

StatusCode MyxAODAnalysis ::finalize() {
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  ATH_MSG_DEBUG("Finalizing " << name() << "...");

  // Release the needed tools

  return StatusCode::SUCCESS;
}

bool MyxAODAnalysis ::cmp1(std::tuple<int, float> a, std::tuple<int, float> b) {
  return std::get<1>(a) > std::get<1>(b);
}

bool MyxAODAnalysis ::cmp2(std::tuple<std::string, int, float> a,
                           std::tuple<std::string, int, float> b) {
  return std::get<2>(a) > std::get<2>(b);
}

int MyxAODAnalysis ::get_origin_pdgid(const xAOD::TruthParticle* a){
  const xAOD::TruthParticle *origin = a;
  while (origin->nParents() >= 1) {
    origin = origin->parent(0);
  }
  return origin->pdgId();
}   

float MyxAODAnalysis ::get_dP3(const xAOD::TruthParticle* a,const xAOD::TruthParticle*b){
  return (a->p4()-b->p4()).Vect().Mag();
}

std::vector<std::vector<const xAOD::TruthParticle*>> MyxAODAnalysis ::get_ancestor_tree(const xAOD::TruthParticle* a){
  std::vector<std::vector<const xAOD::TruthParticle*>> vec_ancestor;

  std::vector<const xAOD::TruthParticle*> vec_ancestor_0Layer;
  vec_ancestor_0Layer.push_back(a);
  vec_ancestor.push_back(vec_ancestor_0Layer);
 std::cout<<"\nanalyzed particle:"<<a->pdgId()<<"("<<a->barcode()<<")("<<a->pt()/1000<<")("<<a->status()<<"),"<<"\n";
  int n =1;
  while(1){
    std::vector<const xAOD::TruthParticle*> vec_ancestor_NLayer;
    auto vec_ancestor_Nminus1_Layer = vec_ancestor.at(n-1);
    std::cout<<"layer:"<<n<<"\n";
    for (int i = 0; i < vec_ancestor_Nminus1_Layer.size(); ++i){
      auto part=vec_ancestor_Nminus1_Layer.at(i);
      for (std::size_t i = 0; i < part->nParents(); ++i){
        auto parent=part->parent(i);
        vec_ancestor_NLayer.push_back(parent);
        std::cout<<parent->pdgId()<<"("<<parent->barcode()<<")("<<parent->pt()/1000<<")("<<parent->status()<<"),";
      }
      std::cout<<"|";
    }
    std::cout<<"  layer size:"<<vec_ancestor_NLayer.size();
    ++n; std::cout<<"\n";
    if (vec_ancestor_NLayer.size()==0) break;
    vec_ancestor.push_back(vec_ancestor_NLayer);
  }
  
  return vec_ancestor;
}  

void MyxAODAnalysis ::record_ancestor_tree(const xAOD::TruthParticle* a,TH1* hist_origin,TH1* hist_ancestor,float weight){
  std::vector<std::vector<const xAOD::TruthParticle*>> vec_ancestor;

  std::vector<const xAOD::TruthParticle*> vec_ancestor_0Layer;
  vec_ancestor_0Layer.push_back(a);
  vec_ancestor.push_back(vec_ancestor_0Layer);
  int n =1;
  while(1){
    std::vector<const xAOD::TruthParticle*> vec_ancestor_NLayer;
    auto vec_ancestor_Nminus1_Layer = vec_ancestor.at(n-1);

    for (int i = 0; i < vec_ancestor_Nminus1_Layer.size(); ++i){
      auto part=vec_ancestor_Nminus1_Layer.at(i);
      if (part->nParents()==0) hist_origin->Fill(part->pdgId(), weight);
      for (std::size_t i = 0; i < part->nParents(); ++i){
        vec_ancestor_NLayer.push_back(part->parent(i));
        hist_ancestor->Fill(part->parent(i)->pdgId(), weight);
      }

    }
    ++n; 
    if (vec_ancestor_NLayer.size()==0) break;
    vec_ancestor.push_back(vec_ancestor_NLayer);
  }
}  

  std::vector<std::vector<const xAOD::TruthParticle*>> MyxAODAnalysis ::get_descender_tree(const xAOD::TruthParticle* a){
  std::vector<std::vector<const xAOD::TruthParticle*>> vec_descender;

  std::vector<const xAOD::TruthParticle*> vec_descender_0Layer;
  vec_descender_0Layer.push_back(a);
  vec_descender.push_back(vec_descender_0Layer);
  std::cout<<"\nanalyzed particle:"<<a->pdgId()<<"("<<a->barcode()<<")("<<a->pt()/1000<<")("<<a->status()<<"),"<<"\n";
  int n =1;
  while(1){
    std::vector<const xAOD::TruthParticle*> vec_descender_NLayer;
    auto vec_descender_Nminus1_Layer = vec_descender.at(n-1);
    std::cout<<"layer:"<<n<<"\n";
    for (int i = 0; i < vec_descender_Nminus1_Layer.size(); ++i){
      auto part=vec_descender_Nminus1_Layer.at(i);
      float ptsum =0;
      TLorentzVector TLV_sum;
      for (std::size_t i = 0; i < part->nChildren(); ++i){
        auto child = part->child(i);
        vec_descender_NLayer.push_back(child);
        std::cout<<child->pdgId()<<"("<<child->barcode()<<")("<<child->pt()/1000<<")("<<child->status()<<"),";
        ptsum+=child->pt();
        TLV_sum+=child->p4();
      }
      //std::cout<<"("<<ptsum/1000<<")("<<TLV_sum.Pt()/1000<<")|";
      //std::cout<<"|";
      std::cout<<"("<<TLV_sum.Pt()/1000<<")|";
    }
    std::cout<<"  layer size:"<<vec_descender_NLayer.size();
    ++n; std::cout<<"\n";
    if (vec_descender_NLayer.size()==0) break;
    vec_descender.push_back(vec_descender_NLayer);
  }
  
  return vec_descender;
}  
     