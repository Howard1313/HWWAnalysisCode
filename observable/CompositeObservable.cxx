#include "HWWAnalysisCode/CompositeObservable.h"
#include <limits>
// uncomment the following line to enable debug printouts
#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);
// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

#include <limits>
#include <string.h>
#include <iostream>
#include <map>
#include "TMath.h"

#include "xAODParticleEvent/CompositeParticleContainer.h"
#include "xAODParticleEvent/ParticleContainer.h"
#include "xAODMissingET/MissingETContainer.h"

ClassImp(CompositeObservable)

//______________________________________________________________________________________________
CompositeObservable::CompositeObservable()
{
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________
CompositeObservable::~CompositeObservable(){
  // default destructor
  DEBUGclass("destructor called");
}
#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"
//______________________________________________________________________________________________
double CompositeObservable::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");
  // the TQEventObservable only works in an ASG RELEASE, hence
  // we encapsulate the implementation in an ifdef/ifndef block
  #ifndef HAS_XAOD
  #warning "using plain ROOT compilation scheme - please add an ASG Analysis Release in order to use this feature!"
  return std::numeric_limits<double>::quiet_NaN();
  #else
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!
  // first, you can retrieve the data members you needwith the 'retrieve' method
  // as arguments to this function, pass the member pointer to the container as well as the container name
  /* example block:
  xAOD::CompositeParticleContainer* cont = NULL;
  this->retrieve(cont, "EECands");
  */
  // after you have retrieved your data members, you can proceed to calculate the return value
  // probably, you first have to retrieve an element from the container
  /* example block:
  const CompositeParticle* p = cont->at(0);
  */
  // in the end, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* exmple block:
  const double retval = p->electron(0)->passSelection(this->fExpression.Data());
  */
  if(!this->fEvent->retrieve(this->mCand, this->mCandName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return 0;
  }
  // DEBUGclass("retrieve candidates! %s",this->mCandName.Data());
  const xAOD::CompositeParticle *Evt = this->mCand->at(0);
  // DEBUGclass(" this->mCand->size() %i",this->mCand->size());

  if(this->mCand->size()==0) return 0.;
  // lepton of interest
  //1st loop
  DEBUGclass("============================ CompositeParticle info start ===============================");
  float sumPt_SRjet=0;

  std::vector< const xAOD::Jet*> vecjet;
  std::vector< const xAOD::Jet*> vecSRjet;
  std::vector<const xAOD::Muon*> vecmuon;
  std::vector<const xAOD::Muon*> vecmuon_p;
  std::vector<const xAOD::Muon*> vecmuon_m;
  std::vector<const xAOD::Electron*> vecele;
  std::vector<const xAOD::Electron*> vecele_p;
  std::vector<const xAOD::Electron*> vecele_m;
  std::vector<std::tuple<const xAOD::IParticle*, int>>veclep;

//1st loop
  DEBUGclass("============================ event info start ===============================");
  for (std::size_t n = 0; n < Evt->nParts(); ++n){
    if (Evt->part(n)->type()==xAOD::Type::Jet) {
      const xAOD::Jet* jet = Evt->jet(n);
      if (jet->m()/1000>40) vecjet.push_back(jet);
    }

    if (Evt->part(n)->type()==xAOD::Type::Muon){
      const xAOD::Muon *muon = Evt->muon(n);
      int muon_charge = muon->charge();
      if (muon_charge==1) vecmuon_p.push_back(muon);
      if (muon_charge==-1) vecmuon_m.push_back(muon);
      vecmuon.push_back(muon);
      veclep.push_back({muon,muon_charge});
    }
    if (Evt->part(n)->type()==xAOD::Type::Electron){
      const xAOD::Electron* ele=Evt->electron(n);
      int ele_charge = ele->charge();
      if (ele_charge==1) vecele_p.push_back(ele);
      if (ele_charge==-1) vecele_m.push_back(ele);
      vecele.push_back(ele);
      veclep.push_back({ele,ele_charge});
    }    
  }

  for (std::size_t n = 0; n < Evt->nOtherParts(); ++n){
    if (Evt->otherPart(n)->type()==xAOD::Type::Jet){
      const xAOD::Jet *jet = Evt->otherJet(n);
      vecSRjet.push_back(jet);
    }
    if (Evt->otherPart(n)->type()==xAOD::Type::Muon){
      const xAOD::Muon *muon = Evt->otherMuon(n);
      int muon_charge = muon->charge();
      if (muon_charge==1) vecmuon_p.push_back(muon);
      if (muon_charge==-1) vecmuon_m.push_back(muon);
      vecmuon.push_back(muon);
      veclep.push_back({muon,muon_charge});
    }
    if (Evt->otherPart(n)->type()==xAOD::Type::Electron){
      const xAOD::Electron* ele=Evt->otherElectron(n);
      int ele_charge = ele->charge();
      if (ele_charge==1) vecele_p.push_back(ele);
      if (ele_charge==-1) vecele_m.push_back(ele);
      vecele.push_back(ele);
      veclep.push_back({ele,ele_charge});
    }    
  }



  int nmuon=vecmuon.size();
  int nmuon_p=vecmuon_p.size();
  int nmuon_m=vecmuon_m.size();
  int nele=vecele.size();
  int nele_p=vecele_p.size();
  int nele_m=vecele_m.size();
  int njet=vecjet.size();
  int nSRjet=vecSRjet.size();
  int nlep=veclep.size();

  std::sort(vecjet.begin(), vecjet.end(), cmp_pt_Jet );
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt_Muon );
  std::sort(vecmuon_p.begin(), vecmuon_p.end(), cmp_pt_Muon );
  std::sort(vecmuon_m.begin(), vecmuon_m.end(), cmp_pt_Muon );
  std::sort(vecele.begin(), vecele.end(), cmp_pt_Electron );
  std::sort(vecele_p.begin(), vecele_p.end(), cmp_pt_Electron );
  std::sort(vecele_m.begin(), vecele_m.end(), cmp_pt_Electron );

  // if (njet>=1){
  //   auto cmp_jet1_dR = [vecjet](std::tuple<const xAOD::IParticle*, int> a, std::tuple<const xAOD::IParticle*, int> b) -> bool
  //   { 
  //     return std::get<0>(a)->p4().DeltaR(vecjet.at(0)->p4()) < std::get<0>(b)->p4().DeltaR(vecjet.at(0)->p4());
  //   };
  //   std::sort(veclep.begin(), veclep.end(), cmp_jet1_dR );
  // }

  std::sort(veclep.begin(), veclep.end(), cmp_pt_IParticle );

  const xAOD::MissingET *METCand = Evt->missingET();
  TLorentzVector miss(METCand->mpx(),METCand->mpy(),0,METCand->met());

  float dvalue=9999999;
  TLorentzVector jet1(dvalue,dvalue,dvalue,dvalue);
  if (njet>=1) jet1 = vecjet.at(0)->p4();
  TLorentzVector jet2(dvalue,dvalue,dvalue,dvalue);
  if (njet>=2) jet2 = vecjet.at(1)->p4();
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
  if (nlep>=1) lep1 = std::get<0>(veclep.at(0))->p4(); 
  TLorentzVector lep2(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=2) lep2 = std::get<0>(veclep.at(1))->p4();
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
  // TLorentzVector muon_uniChar(dvalue,dvalue,dvalue,dvalue);
  // if (nmuon_p==2 && nmuon_m==1) muon_uniChar = up2;
  // if (nmuon_m==2 && nmuon_p==1) muon_uniChar = um2;

  DEBUGclass("nmuon:%i nele:%i njet:%i",nmuon,nele,njet);

  float Zmass = 91187.6; // MeV
  float Wmass = 80377; // MeV
  TLorentzVector up_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector muon3_method2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p==2 && nmuon_m==1) {
    float M_up1um1 = (up1+um1).M();
    float M_up2um1 = (up2+um1).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up2um1-Zmass)) {muon3_method2 = up1; up_method2=up2; um_method2=um1;}
    if (abs(M_up1um1-Zmass)<=abs(M_up2um1-Zmass)) {muon3_method2 = up2; up_method2=up1; um_method2=um1;}
  }
  if (nmuon_p==1 && nmuon_m==2) {
    float M_up1um1 = (up1+um1).M();
    float M_up1um2 = (up1+um2).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up1um2-Zmass)) {muon3_method2 = um1; up_method2=up1; um_method2=um2;}
    if (abs(M_up1um1-Zmass)<=abs(M_up1um2-Zmass)) {muon3_method2 = um2; up_method2=up1; um_method2=um1;}
  }
  //DEBUGclass("up_method2 pt:%f um_method2 pt:%f muon3_method2 pt:%f",up_method2.Pt(),um_method2.Pt(),muon3_method2.Pt());

  if (nmuon_p==1 && nmuon_m==1){
    up_method2=up1;um_method2=um1;
  }

  TLorentzVector up(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector u3(dvalue,dvalue,dvalue,dvalue);

  // int n_match=0;
  // if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {
  //   for (int i = 0; i < njet; ++i){
  //     auto jet = vecjet.at(i)->p4();
  //     if(jet.DeltaR(muon_uniChar)<1) n_match++;
  //   }
  //   if(n_match==1){up=up1; um=um1; u3=muon_uniChar;}
  //   else {up=up_method2; um=um_method2; u3=muon3_method2;}
  // }
  up=up_method2; um=um_method2; u3=muon3_method2;

  std::vector<TLorentzVector> vec_Zlep;
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {vec_Zlep.push_back(up);vec_Zlep.push_back(um);}
  if(nmuon_p==1 && nmuon_m==1 && nele==1) {vec_Zlep.push_back(up);vec_Zlep.push_back(um);}
  if(nele_p>=1 && nele_m>=1 && nmuon>=1) {vec_Zlep.push_back(ep);vec_Zlep.push_back(em);}
  std::sort(vec_Zlep.begin(), vec_Zlep.end(), cmp_pt_TLorentzVector );

  TLorentzVector Hlep(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector VWlep(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector Zlep1(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector Zlep2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector ZBoson(dvalue,dvalue,dvalue,dvalue);
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {Hlep = u3; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;}
  if(nmuon_p==1 && nmuon_m==1 && nele==1) {Hlep = ele1; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;}
  if(nele_p>=1 && nele_m>=1 && nmuon>=1) {Hlep = muon1; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;}
  if(nlep==2) {Hlep = lep2; VWlep = lep1;}
  if(nmuon==1 && nele==0) {VWlep = lep1;}

  TLorentzVector SRjet1_l2(0,0,0,0);
  TLorentzVector SRjet2_l2(0,0,0,0);
  TLorentzVector l2Wjj(0,0,0,0);
  TLorentzVector SRjet1_l1(0,0,0,0);
  TLorentzVector SRjet2_l1(0,0,0,0);
  TLorentzVector l1Wjj(0,0,0,0);
  int Wjj_count = 0;
  if(nlep==2){
    auto cmp_lep2_dR = [lep2](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
    { 
      return a->p4().DeltaR(lep2) < b->p4().DeltaR(lep2);
    };
    std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_lep2_dR );
    if (nSRjet>=1) SRjet1_l2 = vecSRjet.at(0)->p4();
    if (nSRjet>=2) SRjet2_l2 = vecSRjet.at(1)->p4();
    if (nSRjet>=2) l2Wjj = SRjet1_l2+SRjet2_l2;

    auto cmp_lep1_dR = [lep1](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
    { 
      return a->p4().DeltaR(lep1) < b->p4().DeltaR(lep1);
    };
    std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_lep1_dR );
    if (nSRjet>=1) SRjet1_l1 = vecSRjet.at(0)->p4();
    if (nSRjet>=2) SRjet2_l1 = vecSRjet.at(1)->p4();
    if (nSRjet>=2) l1Wjj = SRjet1_l1+SRjet2_l1;

    int l1_flag =0;
    int l2_flag =0;
    if(abs(l1Wjj.M()-Wmass)/1000<20) l1_flag=1;
    if(abs(l2Wjj.M()-Wmass)/1000<20) l2_flag=1;
    if(l1_flag==1) {Hlep = lep1; VWlep = lep2;}
    if(l2_flag==1) {Hlep = lep2; VWlep = lep1;}
    if(l1_flag==1 && l2_flag==1) {Hlep = lep2; VWlep = lep1;}
    Wjj_count = l1_flag + l2_flag;
  }


  TLorentzVector SRjet1_Hl(0,0,0,0);
  TLorentzVector SRjet2_Hl(0,0,0,0);
  TLorentzVector HlWjj(0,0,0,0);
  auto cmp_Hlep_dR = [Hlep](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  { 
    return a->p4().DeltaR(Hlep) < b->p4().DeltaR(Hlep);
  };
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_Hlep_dR );
  if (nSRjet>=1) SRjet1_Hl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Hl = vecSRjet.at(1)->p4();
  if (nSRjet>=2) HlWjj = SRjet1_Hl+SRjet2_Hl;

  TLorentzVector SRjet1_Vl(0,0,0,0);
  TLorentzVector SRjet2_Vl(0,0,0,0);
  TLorentzVector VlWjj(0,0,0,0);
  auto cmp_VWlep_dR = [VWlep](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  { 
    return a->p4().DeltaR(VWlep) < b->p4().DeltaR(VWlep);
  };
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_VWlep_dR );
  if (nSRjet>=1) SRjet1_Vl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Vl = vecSRjet.at(1)->p4();
  if (nSRjet>=2) VlWjj = SRjet1_Vl+SRjet2_Vl;

  std::vector<TLorentzVector> vec_Hfatjet_cand;
  vec_Hfatjet_cand.push_back(jet1);vec_Hfatjet_cand.push_back(jet2);vec_Hfatjet_cand.push_back(HlWjj);
  auto cmp_Wmass_dM = [Wmass](TLorentzVector a, TLorentzVector b) -> bool
  { 
    return abs(a.M()-Wmass) < abs(b.M()-Wmass);
  };
  std::sort(vec_Hfatjet_cand.begin(), vec_Hfatjet_cand.end(), cmp_Wmass_dM );
  TLorentzVector Hfatjet = vec_Hfatjet_cand.at(0);
  if(nele>=1 && nSRjet>=2) {Hfatjet=HlWjj;}


  TLorentzVector all_vis(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector HBoson(dvalue,dvalue,dvalue,dvalue);
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {HBoson = Hfatjet+Hlep; all_vis = ZBoson+HBoson;}
  if(nmuon_p==1 && nmuon_m==1 && nele==1) {HBoson = Hfatjet+Hlep; all_vis = ZBoson+HBoson;}
  if(nele_p>=1 && nele_m>=1 && nmuon>=1) {HBoson = Hfatjet+Hlep; all_vis = ZBoson+HBoson;}
  if(nlep==2) {HBoson = Hfatjet+Hlep; all_vis = HBoson+VWlep;}


  int Vlep_charge = 0;
  if (nlep>=1) Vlep_charge = std::get<1>(veclep.at(0));
  int Hlep_charge = 0;
  if (nlep>=2) Hlep_charge = std::get<1>(veclep.at(1));
  
  TLorentzVector interested_obj1(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector interested_obj2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector zero(0,0,0,0);

  switch (finterested_obj1) {
    case Interested_Obj1::miss: 
        interested_obj1 = miss;
        break;
    case Interested_Obj1::Hlep: 
        interested_obj1 = Hlep;
        break;
    case Interested_Obj1::VWlep: 
        interested_obj1 = VWlep;
        break;
    case Interested_Obj1::Zlep1: 
        interested_obj1 = Zlep1;
        break;
    case Interested_Obj1::Zlep2: 
        interested_obj1 = Zlep2;
        break;
    case Interested_Obj1::ZBoson: 
        interested_obj1 = ZBoson;
        break;
    case Interested_Obj1::Hfatjet: 
        interested_obj1 = Hfatjet;
        break;
    case Interested_Obj1::HBoson: 
        interested_obj1 = HBoson;
        break;
    case Interested_Obj1::all_vis: 
        interested_obj1 = all_vis;
        break;
    case Interested_Obj1::jet1: 
      interested_obj1 = jet1;
      break;
    case Interested_Obj1::l1Wjj: 
      interested_obj1 = l1Wjj;
      break;
    case Interested_Obj1::SRjet1_l1: 
      interested_obj1 = SRjet1_l1;
      break;
    case Interested_Obj1::SRjet2_l1: 
      interested_obj1 = SRjet2_l1;
      break;
    case Interested_Obj1::l2Wjj: 
      interested_obj1 = l2Wjj;
      break;
    case Interested_Obj1::SRjet1_l2: 
      interested_obj1 = SRjet1_l2;
      break;
    case Interested_Obj1::SRjet2_l2: 
      interested_obj1 = SRjet2_l2;
      break;
    case Interested_Obj1::HlWjj: 
      interested_obj1 = HlWjj;
      break;
    case Interested_Obj1::SRjet1_Hl: 
      interested_obj1 = SRjet1_Hl;
      break;
    case Interested_Obj1::SRjet2_Hl: 
      interested_obj1 = SRjet2_Hl;
      break;
    case Interested_Obj1::VlWjj: 
      interested_obj1 = VlWjj;
      break;
    case Interested_Obj1::SRjet1_Vl: 
      interested_obj1 = SRjet1_Vl;
      break;
    case Interested_Obj1::SRjet2_Vl: 
      interested_obj1 = SRjet2_Vl;
      break;
    default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in CompositeObservable :: unrecognised interested_obj1. Check your configuration of this observable.");
  }

 switch (finterested_obj2) {
    case Interested_Obj2::miss: 
        interested_obj2 = miss;
        break;
    case Interested_Obj2::Hlep: 
        interested_obj2 = Hlep;
        break;
    case Interested_Obj2::VWlep: 
        interested_obj2 = VWlep;
        break;
    case Interested_Obj2::Zlep1: 
        interested_obj2 = Zlep1;
        break;
    case Interested_Obj2::Zlep2: 
        interested_obj2 = Zlep2;
        break;
    case Interested_Obj2::ZBoson: 
        interested_obj2 = ZBoson;
        break;
    case Interested_Obj2::Hfatjet: 
        interested_obj2 = Hfatjet;
        break;
    case Interested_Obj2::HBoson: 
        interested_obj2 = HBoson;
        break;
    case Interested_Obj2::all_vis: 
        interested_obj2 = all_vis;
        break;
    case Interested_Obj2::jet1: 
      interested_obj2 = jet1;
      break;
    case Interested_Obj2::l1Wjj: 
      interested_obj2 = l1Wjj;
      break;
    case Interested_Obj2::SRjet1_l1: 
      interested_obj2 = SRjet1_l1;
      break;
    case Interested_Obj2::SRjet2_l1: 
      interested_obj2 = SRjet2_l1;
      break;
    case Interested_Obj2::l2Wjj: 
      interested_obj2 = l2Wjj;
      break;
    case Interested_Obj2::SRjet1_l2: 
      interested_obj2 = SRjet1_l2;
      break;
    case Interested_Obj2::SRjet2_l2: 
      interested_obj2 = SRjet2_l2;
      break;
    case Interested_Obj2::HlWjj: 
      interested_obj2 = HlWjj;
      break;
    case Interested_Obj2::SRjet1_Hl: 
      interested_obj2 = SRjet1_Hl;
      break;
    case Interested_Obj2::SRjet2_Hl: 
      interested_obj2 = SRjet2_Hl;
      break;
    case Interested_Obj2::VlWjj: 
      interested_obj2 = VlWjj;
      break;
    case Interested_Obj2::SRjet1_Vl: 
      interested_obj2 = SRjet1_Vl;
      break;
    case Interested_Obj2::SRjet2_Vl: 
      interested_obj2 = SRjet2_Vl;
      break;
    default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in CompositeObservable :: unrecognised interested_obj2. Check your configuration of this observable.");
  }
  
  float rval=-99;
  switch (finterested_variable) {
    case Interested_CompoVariable::dR: 
        rval = interested_obj1.DeltaR(interested_obj2);
        break;
    case Interested_CompoVariable::dEta: 
        rval = std::abs(interested_obj1.Eta()-interested_obj2.Eta());
        break;
    case Interested_CompoVariable::dPhi: 
        rval = interested_obj1.DeltaPhi(interested_obj2);
        break;
    case Interested_CompoVariable::dPt: 
        rval = std::abs(interested_obj1.Pt()-interested_obj2.Pt())/1000;
        break;
    default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in CompositeObservable :: unrecognised interested_variable. Check your configuration of this observable.");
  }

  return rval;
  #endif
}
//______________________________________________________________________________________________
// getClone override (so we don't have to rely on root streamer)
// TQObservable* CompositeObservable::getClone() const  {
//   // retrieve a clone of this observable
//   TQObservable* obs = NULL;
//   if(this->hasExpression()){
//     obs = this->tryCreateInstanceVirtual(this->getExpression());
//   }
  // if(!obs){
    // obs = (TQObservable*)(this->Clone()); DON'T USE ROOT STREAMER, INSTEAD USE COPY constructor
  //   obs = new CompositeObservable(*this);
  // }
//   if(obs->isInitialized()) obs->finalize();
//   return obs;
// }

//______________________________________________________________________________________________
bool CompositeObservable::initializeSelf(){
  TString CandName = "";
  if(!this->fSample->getTagString("~cand",CandName)) return false;
  //The following is needed in combination with (e.g.) the WHMuonPtCorrectionAlgorithm.
  // The algorithm adds a modified EventCand ("EventCorrWH", possibly with additional systematics suffix) with slightly modified kinematics
  // For the determination of ID/antiID we must use the original kinematics though (the correction itself depends on an object being ID/antiID)
  // -> remove the "Corr" prefix from the cand name here (doesn't affect anyone else)
  TQStringUtils::removeLeadingText(CandName,"Corr"); 
  this->mCandName = "Event"+CandName;
  return true;
}
//______________________________________________________________________________________________
CompositeObservable::CompositeObservable(const TString& name,const int interested_obj1,const int interested_obj2, const int interested_variable):TQEventObservable(name)
{
  finterested_obj1=static_cast<Interested_Obj1>(interested_obj1);
  finterested_obj2=static_cast<Interested_Obj2>(interested_obj2);
  finterested_variable=static_cast<Interested_CompoVariable>(interested_variable);
}

bool CompositeObservable :: cmp_pt_IParticle (std::tuple<const xAOD::IParticle*, int> a,std::tuple<const xAOD::IParticle*, int> b)
{
    return std::get<0>(a)->pt() > std::get<0>(b)->pt();
}

bool CompositeObservable :: cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b)
{
    return a->pt() > b->pt();
}
bool CompositeObservable :: cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b)
{
    return a->pt() > b->pt();
}
bool CompositeObservable :: cmp_pt_TLorentzVector (TLorentzVector a,TLorentzVector b)
{
    return a.Pt() > b.Pt();
}
bool CompositeObservable :: cmp_pt_Jet (const xAOD::Jet* a,const xAOD::Jet* b)
{
    return a->pt() > b->pt();
}

