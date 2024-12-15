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
  ANA_CHECK(book(TH1F("n_ZBoson", "n_ZBoson", 16, 0, 16)));
  ANA_CHECK(book(TH1F("n_HBoson", "n_HBoson", 16, 0, 16)));
  ANA_CHECK(book(TH1F("n_Ze", "n_Ze", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_Zu", "n_Zu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HW", "n_HW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_qdW", "n_qdW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_edW", "n_edW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_udW", "n_udW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_tdW", "n_tdW", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_ldW", "n_ldW", 11, 0, 11)));

  ANA_CHECK(book(TH1F("n_HWde", "n_HWde", 11, 0, 11)));
  // ANA_CHECK(book(TH1F("n_HWdve", "n_HWdve", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdu", "n_HWdu", 11, 0, 11)));
  // ANA_CHECK(book(TH1F("n_HWdvu", "n_HWdvu", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdt", "n_HWdt", 11, 0, 11)));
  // ANA_CHECK(book(TH1F("n_HWdvt", "n_HWdvt", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_HWdcl", "n_HWdcl", 11, 0, 11)));
  ANA_CHECK(book(TH1F("n_match", "n_match", 3, 0, 3)));
  
  // ANA_CHECK(book(TH1F("n_HParent", "n_HParent", 11, 0, 11)));
  // ANA_CHECK(book(TH1F("HP_nParent", "HP_nParent", 11, 0, 11)));
  // ANA_CHECK(book(TH1F("HP_nChild", "HP_nChild", 11, 0, 11)));
  ANA_CHECK(book(TH1F("Hparent_pdgid", "Hparent_pdgid", 60, -30, 30)));

  // ANA_CHECK(book(TH1F("H_status", "H_status", 190, 0, 190)));
  // ANA_CHECK(book(TH1F("Z_status", "Z_status", 190, 0, 190)));
  ANA_CHECK(book(TH1F("H_pt", "H_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Z_pt", "Z_pt[GeV]", 50, 0, 500)));
  ANA_CHECK(book(TH1F("HZ_pt", "HZ_pt[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("dpt_ZH_scalar", "dpt_ZH_scalar[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("sumpt_ZH_vector", "sumpt_ZH_vector[GeV]", 50, 0, 500)));

  ANA_CHECK(book(TH1F("dR_j1Zu1", "dR_j1Zu1", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_j1Zu2", "dR_j1Zu2", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_j1Hu", "dR_j1Hu", 25, 0,5)));
  ANA_CHECK(book(TH1F("Zu1_pt", "Zu1_pt", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Zu2_pt", "Zu2_pt", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Hu_pt", "Hu_pt", 50, 0, 500)));
  
  ANA_CHECK(book(TH1F("muon1_pt", "muon1_pt", 50, 0, 500)));
  ANA_CHECK(book(TH1F("muon2_pt", "muon2_pt", 50, 0, 500)));
  ANA_CHECK(book(TH1F("muon3_pt", "muon3_pt", 50, 0, 500)));
  ANA_CHECK(book(TH1F("jet1_pt", "jet1_pt", 50, 0, 500)));
  
  ANA_CHECK(book(TH1F("dR_Z_jet1_3u", "dR_Z_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_H_jet1_3u", "dR_H_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_qdW_jet1_3u", "dR_qdW_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1qdW_jet1_3u", "dR_jet1qdW_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_H_Z_3u", "dR_H_Z_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Zu1_jet1_3u", "dR_Zu1_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Zu2_jet1_3u", "dR_Zu2_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_jet1_3u", "dR_Hu_jet1_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1_muon3_method2_3u", "dR_jet1_muon3_method2_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1_u3_3u", "dR_jet1_u3_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_u3_muon3_method2_3u", "dR_u3_muon3_method2_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_muon3_method2_3u", "dR_Hu_muon3_method2_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_u3_3u", "dR_Hu_u3_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_up_3u", "dR_Hu_up_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_um_3u", "dR_Hu_um_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_up_um_3u", "dR_up_um_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_Rcu_3u", "dR_Hu_Rcu_3u", 25, 0,5)));
  ANA_CHECK(book(TH1F("ZM_Other_muon_method2", "ZM_Other_muon_method2", 50, 0, 500)));
  ANA_CHECK(book(TH1F("ZM_method2", "ZM_method2", 50, 0, 500)));
  ANA_CHECK(book(TH1F("ZM_method3", "ZM_method3", 50, 0, 500)));
  

  ANA_CHECK(book(TH1F("dR_Z_jet1_1u2e", "dR_Z_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_H_jet1_1u2e", "dR_H_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_qdW_jet1_1u2e", "dR_qdW_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1qdW_jet1_1u2e", "dR_jet1qdW_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_H_Z_1u2e", "dR_H_Z_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Ze1_jet1_1u2e", "dR_Ze1_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Ze2_jet1_1u2e", "dR_Ze2_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_jet1_1u2e", "dR_Hu_jet1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Hu_u1_1u2e", "dR_Hu_u1_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Ze1_ep_1u2e", "dR_Ze1_ep_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Ze1_em_1u2e", "dR_Ze1_em_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_Z_jet2_1u2e", "dR_Z_jet2_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_H_jet2_1u2e", "dR_H_jet2_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("dR_jet1qdW_jet2_1u2e", "dR_jet1qdW_jet2_1u2e", 25, 0,5)));
  ANA_CHECK(book(TH1F("M_jet1_1u2e", "M_jet1_1u2e", 50, 0, 500)));
  ANA_CHECK(book(TH1F("M_jet2_1u2e", "M_jet2_1u2e", 50, 0, 500)));
  ANA_CHECK(book(TH1F("M_jet1qdW_1u2e", "M_jet1qdW_1u2e", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Pt_jet1_1u2e", "Pt_jet1_1u2e", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Pt_jet2_1u2e", "Pt_jet2_1u2e", 50, 0, 500)));
  ANA_CHECK(book(TH1F("Pt_jet1qdW_1u2e", "Pt_jet1qdW_1u2e", 50, 0, 500)));
  
  
  
  ANA_CHECK (book (TTree ("Hpt_Hupt", "Hpt_Hupt ntuple")));
  TTree* mytree = tree ("Hpt_Hupt");
  mytree->Branch ("Hpt", &m_Hpt);
  mytree->Branch ("Hupt", &m_Hupt);
  mytree->Branch ("nmuon", &m_nmuon);
  mytree->Branch ("jet1_pt", &m_jet1_pt);
  mytree->Branch ("muon1_pt", &m_muon1_pt);
  mytree->Branch ("muon2_pt", &m_muon2_pt);
  mytree->Branch ("muon3_pt", &m_muon3_pt);
  //ANA_CHECK(book(TNtuple("Hpt_Hupt","Hpt_Hupt","H_pt:Hu_pt"));
  ANA_CHECK(book(TH1F("njet", "njet", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nSRjet", "nSRjet", 21, 0, 21)));
  ANA_CHECK(book(TH1F("njet_100", "njet_100", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_200", "njet_200", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_300", "njet_300", 11, 0, 11)));
  ANA_CHECK(book(TH1F("njet_400", "njet_400", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon", "nmuon", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon_p", "nmuon_p", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nmuon_m", "nmuon_m", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele", "nele", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele_p", "nele_p", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nele_m", "nele_m", 11, 0, 11)));
  ANA_CHECK(book(TH1F("nlep", "nlep", 11, 0, 11)));


  // ANA_CHECK(book(TH1F("MET", "MET[GeV]", 50, 0, 500)));

  // ANA_CHECK(book(TH1F("sumET", "sumET[GeV]", 50, 0, 500)));

  
  
  // ANA_CHECK(book(TH1F("dP3_Hjet_qdW", "dP3_Hjet_qdW[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("dP3_Hjet1_Hjet2", "dP3_Hjet1_Hjet2[GeV]", 50, 0, 500)));
  // ANA_CHECK(book(TH1F("dP3_Hjet2_qdW", "dP3_Hjet2_qdW[GeV]", 50, 0, 500)));

  

  // ANA_CHECK(book(TH1F("SumPx_lep_jet", "SumPx_lep_jet[GeV]", 100, -500, 500)));
  // ANA_CHECK(book(TH1F("SumPy_lep_jet", "SumPy_lep_jet[GeV]", 100, -500, 500)));
  // ANA_CHECK(book(TH1F("SumPx_lep_SRjet", "SumPx_lep_SRjet[GeV]", 100, -500, 500)));
  // ANA_CHECK(book(TH1F("SumPy_lep_SRjet", "SumPy_lep_SRjet[GeV]", 100, -500, 500)));



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
  ATH_CHECK(evtStore()->retrieve(truthak10jet,"AntiKt10TruthTrimmedPtFrac5SmallR20Jets"));
  ANA_MSG_INFO("retrieve fatjet successfully");

  const xAOD::JetContainer* truthak4jet(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthak4jet, "AntiKt4TruthDressedWZJets"));

  

  int qqZuu_flag = 0;
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
  std::vector<const xAOD::TruthParticle*> vec_ZBoson;
  std::vector<const xAOD::TruthParticle*> vec_Ze;
  std::vector<const xAOD::TruthParticle*> vec_Zu;
  std::vector<const xAOD::TruthParticle*> vec_HW;
  std::vector<const xAOD::TruthParticle*> vec_qdW;
  std::vector<const xAOD::TruthParticle*> vec_edW;
  std::vector<const xAOD::TruthParticle*> vec_udW;
  std::vector<const xAOD::TruthParticle*> vec_tdW;
  std::vector<const xAOD::TruthParticle*> vec_ldW;

  std::vector<const xAOD::TruthParticle*> vec_HWde;
  std::vector<const xAOD::TruthParticle*> vec_HWdu;
  std::vector<const xAOD::TruthParticle*> vec_HWdt;
  
  if (qqZuu_flag == 1) {
    for (std::size_t i = 0; i < truthBoson->size(); ++i) {
      auto ithBoson = truthBoson->at(i);
      hist("Boson_pdgid")->Fill(abs(ithBoson->pdgId()), weight);

      if (abs(ithBoson->pdgId()) == 23) {
        if (ithBoson->nParents() == 0) vec_ZBoson.push_back(ithBoson);
        if (ithBoson->nParents() > 0) if (abs(ithBoson->parent(0)->pdgId()) != 23) vec_ZBoson.push_back(ithBoson);
      }
      
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
   
    if (abs(ithBoson->pdgId()) == 23) {
      if (ithBoson->nParents() == 0) vec_ZBoson.push_back(ithBoson);
      if (ithBoson->nParents() > 0) if (abs(ithBoson->parent(0)->pdgId()) != 23) vec_ZBoson.push_back(ithBoson);
    }

    if (abs(ithBoson->pdgId()) == 23 && ithBoson->nChildren() >0) {
      std::cout <<"nZchild:"<<ithBoson->nChildren()<<std::endl;
      for (std::size_t i = 0; i < ithBoson->nChildren(); ++i){
        auto child = ithBoson->child(i);
        std::cout <<"Z child:"<<child->pdgId()<<std::endl;
        if (child->absPdgId()==11) vec_Ze.push_back(child);
        if (child->absPdgId()==13) vec_Zu.push_back(child);
      }
    }
  
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
          vec_HWde.push_back(child);
        }
        if (abs(child->pdgId())== 13) {
          vec_udW.push_back(ithBoson);
          vec_ldW.push_back(ithBoson);
          vec_HWdu.push_back(child);
        }
        if (abs(child->pdgId())== 15) {
          vec_tdW.push_back(ithBoson);
          vec_ldW.push_back(ithBoson);
          vec_HWdt.push_back(child);
        }
      }  
    }

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
  ANA_MSG_INFO("for loop BosonD successfully");

  int n_HBoson = vec_HBoson.size(); hist("n_HBoson")->Fill(n_HBoson, weight);
  int n_ZBoson = vec_ZBoson.size(); hist("n_ZBoson")->Fill(n_ZBoson, weight);
  int n_Ze = vec_Ze.size(); hist("n_Ze")->Fill(n_Ze, weight);
  int n_Zu = vec_Zu.size(); hist("n_Zu")->Fill(n_Zu, weight);
  int n_qdW = vec_qdW.size(); hist("n_qdW")->Fill(n_qdW, weight);
  int n_edW = vec_edW.size(); hist("n_edW")->Fill(n_edW, weight);
  int n_udW = vec_udW.size(); hist("n_udW")->Fill(n_udW, weight);
  int n_tdW = vec_tdW.size(); hist("n_tdW")->Fill(n_tdW, weight);
  int n_ldW = vec_ldW.size(); hist("n_ldW")->Fill(n_ldW, weight);
  int n_HW = vec_HW.size(); hist("n_HW")->Fill(n_HW, weight);
  int n_HWde = vec_HWde.size(); hist("n_HWde")->Fill(n_HWde, weight);
  int n_HWdu = vec_HWdu.size(); hist("n_HWdu")->Fill(n_HWdu, weight);
  int n_HWdt = vec_HWdt.size(); hist("n_HWdt")->Fill(n_HWdt, weight);
  ANA_MSG_INFO("number variable successfully");
  std::sort(vec_Ze.begin(), vec_Ze.end(), cmp_pt);
  std::sort(vec_Zu.begin(), vec_Zu.end(), cmp_pt);

  
  // HBoson
  const xAOD::TruthParticle* H_Tpart= vec_HBoson.at(0);
  const xAOD::TruthParticle* Z_Tpart= vec_ZBoson.at(0);
  // if(n_Ze>3) auto a  = get_descender_tree(Z_Tpart);
  // const xAOD::TruthParticle* HW_Tpart= vec_ldW.at(0);
  

  // hist("H_status")->Fill(H_Tpart->status(), weight);
  hist("H_pt")->Fill(H_Tpart->pt()/1000, weight);
  // hist("Z_status")->Fill(Z_Tpart->status(), weight);
  hist("Z_pt")->Fill(Z_Tpart->pt()/1000, weight);
  hist("HZ_pt")->Fill((Z_Tpart->p4()+H_Tpart->p4()).Pt()/1000, weight);
  // hist("dpt_ZH_scalar")->Fill((Z_Tpart->pt()-H_Tpart->pt())/1000, weight);
  // hist("sumpt_ZH_vector")->Fill((Z_Tpart->p4()+H_Tpart->p4()).Pt()/1000, weight);

  
  
  hist("n_HWdcl")->Fill(n_HWde+n_HWdu+n_HWdt, weight);



  // float SumPx_lep_jet=0;
  // float SumPx_lep_SRjet=0;
  // float SumPy_lep_jet=0;
  // float SumPy_lep_SRjet=0;
  // //met
  // const xAOD::MissingETContainer *MET_Truth(nullptr);
  // ATH_CHECK(evtStore()->retrieve(MET_Truth, "MET_Truth"));
  // ANA_MSG_INFO("retrieve MET successfully");
  
  // const xAOD::MissingET *METCand = MET_Truth->at(0);
  // TLorentzVector MET_TLV(METCand->mpx(),METCand->mpy(),0,METCand->met());
  // hist("sumET")->Fill(METCand->sumet()/1000, weight);
  
  // construct vecEle
  const xAOD::TruthParticleContainer *truthElectrons(nullptr);
  ATH_CHECK(evtStore()->retrieve(truthElectrons, "TruthElectrons"));
  ANA_MSG_INFO("retrieve electron successfully");

  std::vector<const xAOD::TruthParticle*> vecele;
  std::vector<const xAOD::TruthParticle*> vecele_p;
  std::vector<const xAOD::TruthParticle*> vecele_m;
  for (std::size_t i = 0; i < truthElectrons->size(); ++i) {
    auto ele = truthElectrons->at(i);
    if(ele->pt()/1000>0){
      vecele.push_back(ele);
      if (ele->pdgId() == -11) vecele_p.push_back(ele);
      if (ele->pdgId() == 11) vecele_m.push_back(ele);
    }
    // TLorentzVector ele_TLV=ele->p4();
    // SumPx_lep_jet+=ele_TLV.Px();
    // SumPy_lep_jet+=ele_TLV.Py();
    // SumPx_lep_SRjet+=ele_TLV.Px();
    // SumPy_lep_SRjet+=ele_TLV.Py();
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
    if(muon->pt()/1000>0){
      vecmuon.push_back(muon);
      if (muon->pdgId() == -13) vecmuon_p.push_back(muon);
      if (muon->pdgId() == 13) vecmuon_m.push_back(muon);
    }
    
    
    // auto origin_pdgid=get_origin_pdgid(muon);
    // if(origin_pdgid==25) vec_Horigin_muon.push_back(muon);
    // if(abs(origin_pdgid)==24) vec_Worigin_muon.push_back(muon);
    // if(abs(origin_pdgid)==15) vec_tau_muon.push_back(muon);
    // if(abs(origin_pdgid)==5) vec_bquark_muon.push_back(muon);

    // TLorentzVector muon_TLV=muon->p4();
    // SumPx_lep_jet+=muon_TLV.Px();
    // SumPy_lep_jet+=muon_TLV.Py();
    // SumPx_lep_SRjet+=muon_TLV.Px();
    // SumPy_lep_SRjet+=muon_TLV.Py();
  }
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt);
  std::sort(vecmuon_p.begin(), vecmuon_p.end(), cmp_pt);
  std::sort(vecmuon_m.begin(), vecmuon_m.end(), cmp_pt);
  
  // construct veclep
  std::vector<const xAOD::TruthParticle*> veclep(vecmuon);
  veclep.insert(veclep.end(), vecele.begin(), vecele.end());
  std::sort(veclep.begin(), veclep.end(), cmp_pt);
  
  
  int nmuon = vecmuon.size();  
  int nmuon_p = vecmuon_p.size(); 
  int nmuon_m = vecmuon_m.size(); 
  int nele = vecele.size(); 
  int nele_p = vecele_p.size(); 
  int nele_m = vecele_m.size(); 
  int nlep = veclep.size(); 

  if(nmuon>=1) hist("muon1_pt")->Fill(vecmuon.at(0)->pt()/1000, weight);
  if(nmuon>=2) hist("muon2_pt")->Fill(vecmuon.at(1)->pt()/1000, weight);
  if(nmuon>=3) hist("muon3_pt")->Fill(vecmuon.at(2)->pt()/1000, weight);
  
  if (n_HWdu>=1){
    hist("nmuon")->Fill(nmuon, weight);
    hist("nmuon_p")->Fill(nmuon_p, weight);
    hist("nmuon_m")->Fill(nmuon_m, weight);
    hist("nele")->Fill(nele, weight);
    hist("nele_p")->Fill(nele_p, weight);
    hist("nele_m")->Fill(nele_m, weight);
    hist("nlep")->Fill(nlep, weight); 
  }
  
  
  // construct vecjet
  std::vector<TLorentzVector> vecjet;
  
  for (std::size_t i = 0; i < truthak10jet->size(); ++i) {
    auto jet = truthak10jet->at(i);
    if(jet->pt()/1000>0) vecjet.push_back(jet->p4());
    //vecjet.push_back(jet->p4());
    TLorentzVector jet_TLV=jet->p4();
    // SumPx_lep_jet+=jet_TLV.Px();
    // SumPy_lep_jet+=jet_TLV.Py();
  }
  std::sort(vecjet.begin(), vecjet.end(), cmp_pt);
  int njet=vecjet.size(); hist("njet")->Fill(njet, weight);
  if(njet>=1) hist("jet1_pt")->Fill(vecjet.at(0).Pt()/1000, weight);
  ANA_MSG_INFO("construct vecjet  successfully");

  //dR jet HW
  std::vector<TLorentzVector> vecjet_qdWdR(vecjet);
  auto cmp_TLV_qdWdR = [vec_qdW](TLorentzVector& a, TLorentzVector& b) -> bool
  { 
    return a.DeltaR(vec_qdW.at(0)->p4())< b.DeltaR(vec_qdW.at(0)->p4());
  };
  std::sort(vecjet_qdWdR.begin(), vecjet_qdWdR.end(),cmp_TLV_qdWdR);

  float dvalue=9999999;
  TLorentzVector jet1(dvalue,dvalue,dvalue,dvalue);
  if (njet>=1) jet1 = vecjet.at(0);
  TLorentzVector muon1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=1) muon1 = vecmuon.at(0)->p4();
  TLorentzVector muon2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=2) muon2 = vecmuon.at(1)->p4();
  TLorentzVector muon3(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=3) muon3 = vecmuon.at(2)->p4();
  TLorentzVector ele1(dvalue,dvalue,dvalue,dvalue);
  if (nele>=1) ele1 = vecele.at(0)->p4();
  TLorentzVector ele2(dvalue,dvalue,dvalue,dvalue);
  if (nele>=2) ele2 = vecele.at(1)->p4();
  TLorentzVector lep1(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=1) lep1 = veclep.at(0)->p4();
  TLorentzVector lep2(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=2) lep2 = veclep.at(1)->p4();
  TLorentzVector ep(dvalue,dvalue,dvalue,dvalue);
  if (nele_p>=1) ep = vecele_p.at(0)->p4();
  TLorentzVector em(dvalue,dvalue,dvalue,dvalue);
  if (nele_m>=1) em = vecele_m.at(0)->p4();
  TLorentzVector up1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p>=1) up1 = vecmuon_p.at(0)->p4();
  TLorentzVector up2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p>=2) up2 = vecmuon_p.at(1)->p4();
  TLorentzVector um1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_m>=1) um1 = vecmuon_m.at(0)->p4();
  TLorentzVector um2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_m>=2) um2 = vecmuon_m.at(1)->p4();

  std::vector<const xAOD::TruthParticle*> vec_muon_uniChar(vecmuon);
  if (nmuon_p==2 && nmuon_m==1) vec_muon_uniChar=vecmuon_p;
  if (nmuon_m==2 && nmuon_p==1) vec_muon_uniChar=vecmuon_m;
    
  // TLorentzVector muon_uniChar(dvalue,dvalue,dvalue,dvalue);
  // if (nmuon_p==2 && nmuon_m==1) muon_uniChar = up2;
  // if (nmuon_m==2 && nmuon_p==1) muon_uniChar = um2;
  
  float Zmass = 91187.6; // MeV
  TLorentzVector up_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector muon3_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector theOther_muon_method2(dvalue,dvalue,dvalue,dvalue);
  float ZM_Other_muon_method2(dvalue);
  if (nmuon_p==2 && nmuon_m==1) {
    float M_up1um1 = (up1+um1).M();
    float M_up2um1 = (up2+um1).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up2um1-Zmass)) {muon3_method2 = up1; up_method2=up2; um_method2=um1;theOther_muon_method2=up2;}
    if (abs(M_up1um1-Zmass)<=abs(M_up2um1-Zmass)) {muon3_method2 = up2; up_method2=up1; um_method2=um1;theOther_muon_method2=up1;}
    ZM_Other_muon_method2=(muon3_method2+um1).M();
  }
  if (nmuon_p==1 && nmuon_m==2) {
    float M_up1um1 = (up1+um1).M();
    float M_up1um2 = (up1+um2).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up1um2-Zmass)) {muon3_method2 = um1; up_method2=up1; um_method2=um2;theOther_muon_method2=um2;}
    if (abs(M_up1um1-Zmass)<=abs(M_up1um2-Zmass)) {muon3_method2 = um2; up_method2=up1; um_method2=um1;theOther_muon_method2=um1;}
    ZM_Other_muon_method2=(muon3_method2+up1).M();
  }
  
  TLorentzVector up(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector u3(dvalue,dvalue,dvalue,dvalue);

  if (nmuon_p==2 && nmuon_m==1) {
    float dR_upum=up_method2.DeltaR(um_method2);
    if ((dR_upum<0.2||dR_upum>1.5) && std::abs(ZM_Other_muon_method2-Zmass)<15000){
      um=um1;up=muon3_method2;u3=theOther_muon_method2;
    }
    else {um=um_method2;up=up_method2;u3=muon3_method2;}
  }

  if (nmuon_m==2 && nmuon_p==1) {
    float dR_upum=up_method2.DeltaR(um_method2);
    if ((dR_upum<0.2||dR_upum>1.5) && std::abs(ZM_Other_muon_method2-Zmass)<15000){
      um=muon3_method2;up=up1;u3=theOther_muon_method2;
    }
    else {um=um_method2;up=up_method2;u3=muon3_method2;}
  }
  
  // int n_match=0;
  // if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {
  //   for (int j = 0; j < vec_muon_uniChar.size(); ++j){
  //     auto muon_uniChar=vec_muon_uniChar.at(j);
  //     const xAOD::TruthParticle* theOther_muon;
  //     if (j==0) theOther_muon=vec_muon_uniChar.at(1);
  //     if (j==1) theOther_muon=vec_muon_uniChar.at(0);
  //     for (int i = 0; i < njet; ++i){
  //       auto jet = vecjet.at(i);
  //       if(jet.DeltaR(muon_uniChar->p4())<1) {
  //         n_match++;
  //         u3=muon_uniChar->p4();
  //         if(nmuon_p==2) {up=theOther_muon->p4(); um=um1;}
  //         if(nmuon_m==2) {um=theOther_muon->p4(); up=up1;}
  //       }
  //     }
  //   }
  //   if(n_match!=1){up=up_method2; um=um_method2; u3=muon3_method2;}
  // }

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


  
  if (njet >= 1){
    if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1){
      hist("dR_Z_jet1_3u")->Fill(vecjet.at(0).DeltaR(Z_Tpart->p4()), weight);
      hist("dR_H_jet1_3u")->Fill(vecjet.at(0).DeltaR(H_Tpart->p4()), weight);
      hist("dR_H_Z_3u")->Fill(Z_Tpart->p4().DeltaR(H_Tpart->p4()), weight);
      if(n_Zu==2 && n_HWdu>=1) {
        // hist("n_match")->Fill(n_match, weight);
        hist("dR_Zu1_jet1_3u")->Fill(vecjet.at(0).DeltaR(vec_Zu.at(0)->p4()), weight);
        hist("dR_Zu2_jet1_3u")->Fill(vecjet.at(0).DeltaR(vec_Zu.at(1)->p4()), weight);
        hist("dR_Hu_jet1_3u")->Fill(vecjet.at(0).DeltaR(vec_HWdu.at(0)->p4()), weight);

        hist("dR_jet1_muon3_method2_3u")->Fill(muon3_method2.DeltaR(jet1), weight);
        hist("dR_jet1_u3_3u")->Fill(u3.DeltaR(jet1), weight);
        hist("dR_u3_muon3_method2_3u")->Fill(muon3_method2.DeltaR(u3), weight);
        hist("dR_Hu_muon3_method2_3u")->Fill(muon3_method2.DeltaR(vec_HWdu.at(0)->p4()), weight);
        hist("dR_Hu_u3_3u")->Fill(u3.DeltaR(vec_HWdu.at(0)->p4()), weight);
        hist("dR_Hu_up_3u")->Fill(up.DeltaR(vec_HWdu.at(0)->p4()), weight);
        hist("dR_Hu_um_3u")->Fill(um.DeltaR(vec_HWdu.at(0)->p4()), weight);
        hist("dR_up_um_3u")->Fill(um.DeltaR(up), weight);
        hist("ZM_Other_muon_method2")->Fill(ZM_Other_muon_method2/1000, weight);
        hist("ZM_method2")->Fill((up_method2+um_method2).M()/1000, weight);
        hist("ZM_method3")->Fill((up+um).M()/1000, weight);

        hist("dR_Hu_Rcu_3u")->Fill(std::min(std::min(vecmuon.at(0)->p4().DeltaR(vec_HWdu.at(0)->p4()),vecmuon.at(1)->p4().DeltaR(vec_HWdu.at(0)->p4())),vecmuon.at(2)->p4().DeltaR(vec_HWdu.at(0)->p4())), weight);
        hist("dR_qdW_jet1_3u")->Fill(vecjet.at(0).DeltaR(vec_qdW.at(0)->p4()), weight);
        hist("dR_jet1qdW_jet1_3u")->Fill(vecjet.at(0).DeltaR(vecjet_qdWdR.at(0)), weight);
      }
    }
     if(nmuon==1 && nele_p>=1 && nele_m>=1){
      hist("dR_Z_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(Z_Tpart->p4()), weight);
      hist("dR_H_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(H_Tpart->p4()), weight);
      hist("dR_H_Z_1u2e")->Fill(Z_Tpart->p4().DeltaR(H_Tpart->p4()), weight);
      if(n_Ze==2 && n_HWdu>=1) {
        hist("dR_Ze1_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(vec_Ze.at(0)->p4()), weight);
        hist("dR_Ze2_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(vec_Ze.at(1)->p4()), weight);
        hist("dR_Hu_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(vec_HWdu.at(0)->p4()), weight);
        
        hist("dR_Hu_u1_1u2e")->Fill(muon1.DeltaR(vec_HWdu.at(0)->p4()), weight);
        hist("dR_Ze1_ep_1u2e")->Fill(ep.DeltaR(vec_Ze.at(0)->p4()), weight);
        hist("dR_Ze1_em_1u2e")->Fill(em.DeltaR(vec_Ze.at(0)->p4()), weight);

        hist("dR_qdW_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(vec_qdW.at(0)->p4()), weight);
        hist("dR_jet1qdW_jet1_1u2e")->Fill(vecjet.at(0).DeltaR(vecjet_qdWdR.at(0)), weight);
        if (njet >= 2){
          hist("dR_Z_jet2_1u2e")->Fill(vecjet.at(1).DeltaR(Z_Tpart->p4()), weight);
          hist("dR_H_jet2_1u2e")->Fill(vecjet.at(1).DeltaR(H_Tpart->p4()), weight);
          hist("dR_jet1qdW_jet2_1u2e")->Fill(vecjet.at(1).DeltaR(vecjet_qdWdR.at(0)), weight);
          hist("M_jet1_1u2e")->Fill(vecjet.at(0).M()/1000, weight);
          hist("M_jet2_1u2e")->Fill(vecjet.at(1).M()/1000, weight);
          hist("M_jet1qdW_1u2e")->Fill(vecjet_qdWdR.at(0).M()/1000, weight);
          hist("Pt_jet1_1u2e")->Fill(vecjet.at(0).Pt()/1000, weight);
          hist("Pt_jet2_1u2e")->Fill(vecjet.at(1).Pt()/1000, weight);
          hist("Pt_jet1qdW_1u2e")->Fill(vecjet_qdWdR.at(0).Pt()/1000, weight);
        }
      }
    }
  }
  
  if(njet>0 && n_Zu>=1) hist("dR_j1Zu1")->Fill(vecjet.at(0).DeltaR(vec_Zu.at(0)->p4()), weight);
  if(njet>0 && n_Zu>=2) hist("dR_j1Zu2")->Fill(vecjet.at(0).DeltaR(vec_Zu.at(1)->p4()), weight);
  if(njet>0 && n_HWdu>=1) hist("dR_j1Hu")->Fill(vecjet.at(0).DeltaR(vec_HWdu.at(0)->p4()), weight);
  if(n_Zu>=1) hist("Zu1_pt")->Fill(vec_Zu.at(0)->pt()/1000, weight);
  if(n_Zu>=2) hist("Zu2_pt")->Fill(vec_Zu.at(1)->pt()/1000, weight);
  if(n_HWdu>=1) hist("Hu_pt")->Fill(vec_HWdu.at(0)->pt()/1000, weight);
  ANA_MSG_INFO("hist fill successfully");


  m_Hpt->clear();
  m_Hupt->clear();
  m_nmuon->clear();
  m_jet1_pt->clear();
  m_muon1_pt->clear();
  m_muon2_pt->clear();
  m_muon3_pt->clear();
  if(nmuon>=3){
    if(n_HWdu>=1){
      m_Hupt->push_back(vec_HWdu.at(0)->pt()/1000);
    }
    m_Hpt->push_back(H_Tpart->pt()/1000);
    m_nmuon->push_back(nmuon);
    m_muon1_pt->push_back(vecmuon.at(0)->pt()/1000);
    m_muon2_pt->push_back(vecmuon.at(1)->pt()/1000);
    m_muon3_pt->push_back(vecmuon.at(2)->pt()/1000);
    //m_jet1_pt->push_back(vecjet.at(0).Pt()/1000);
  }
  tree ("Hpt_Hupt")->Fill ();
  ANA_MSG_INFO("tree fill successfully");
  // //dR jet VW
  // std::vector<TLorentzVector> vecjet_VWdR(vecjet);
  // auto cmp_TLV_VWdR = [VW_Tpart](TLorentzVector& a, TLorentzVector& b) -> bool
  // { 
  //   return a.DeltaR(VW_Tpart->p4())< b.DeltaR(VW_Tpart->p4());
  // };
  // std::sort(vecjet_VWdR.begin(), vecjet_VWdR.end(),cmp_TLV_VWdR);
  
   
  // //dR jet HW
  // std::vector<TLorentzVector> vecjet_HWdR(vecjet);
  // auto cmp_TLV_HWdR = [HW_Tpart](TLorentzVector& a, TLorentzVector& b) -> bool
  // { 
  //   return a.DeltaR(HW_Tpart->p4())< b.DeltaR(HW_Tpart->p4());
  // };
  // std::sort(vecjet_HWdR.begin(), vecjet_HWdR.end(),cmp_TLV_HWdR);
  

  

  // //dR SRjet VW
  // std::vector<TLorentzVector> vecSRjet_VWdR(vecSRjet);
  // std::sort(vecSRjet_VWdR.begin(), vecSRjet_VWdR.end(),cmp_TLV_VWdR);
  
   
  // //dR SRjet HW
  // std::vector<TLorentzVector> vecSRjet_HWdR(vecSRjet);
  // std::sort(vecSRjet_HWdR.begin(), vecSRjet_HWdR.end(),cmp_TLV_HWdR);

  
  

  
  
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
  delete m_Hpt;
  delete m_Hupt;
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
     