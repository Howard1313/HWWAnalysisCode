#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <TH1.h>

#include "PMGTools/PMGTruthWeightTool.h"
#include "xAODJet/JetContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include <AsgMessaging/MessageCheck.h>

class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

private:
  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;
  static bool cmp1(std::tuple<int,float>a,std::tuple<int,float>b);
  static bool cmp2(std::tuple<std::string, int, float>a,std::tuple<std::string, int, float>b);
  // static bool cmp_pt(const xAOD::TruthParticle* a,const xAOD::TruthParticle* b);
  // static bool cmp_pt(TLorentzVector a,TLorentzVector b);
  class Cmp_pt {
  public:
    bool operator() (const xAOD::TruthParticle* a,const xAOD::TruthParticle* b) { // something 
        return a->pt() > b->pt();
    }
    bool operator() (TLorentzVector a,TLorentzVector b) { // something 
        return a.Pt() > b.Pt();
    }
  } cmp_pt;
  int get_origin_pdgid(const xAOD::TruthParticle* a);
  float get_dP3(const xAOD::TruthParticle* a,const xAOD::TruthParticle*b);
  std::vector<std::vector<const xAOD::TruthParticle*>> get_ancestor_tree(const xAOD::TruthParticle* a);
  std::vector<std::vector<const xAOD::TruthParticle*>> get_descender_tree(const xAOD::TruthParticle* a);
  void record_ancestor_tree(const xAOD::TruthParticle* a,TH1* hist_origin,TH1* hist_ancestor,float weight);
};
#endif