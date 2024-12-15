#include "HWWAnalysisCode/lvqqObservable.h"
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

ClassImp(lvqqObservable)

//______________________________________________________________________________________________
lvqqObservable::lvqqObservable()
{
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________
lvqqObservable::~lvqqObservable(){
  // default destructor
  DEBUGclass("destructor called");
}
#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"
//______________________________________________________________________________________________
double lvqqObservable::getValue() const {
  DEBUGclass("entering function");

  if(!this->fEvent->retrieve(this->mCand, this->mCandName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return 0;
  }

  const xAOD::CompositeParticle *Evt = this->mCand->at(0);
  // DEBUGclass(" this->mCand->size() %i",this->mCand->size());

  if(this->mCand->size()==0) return 0.;

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
      sumPt_SRjet+=jet->pt();
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
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_pt_Jet );
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt_Muon );
  std::sort(vecmuon_p.begin(), vecmuon_p.end(), cmp_pt_Muon );
  std::sort(vecmuon_m.begin(), vecmuon_m.end(), cmp_pt_Muon );
  std::sort(vecele.begin(), vecele.end(), cmp_pt_Electron );
  std::sort(vecele_p.begin(), vecele_p.end(), cmp_pt_Electron );
  std::sort(vecele_m.begin(), vecele_m.end(), cmp_pt_Electron );
  std::sort(veclep.begin(), veclep.end(), cmp_pt_IParticle );

  const xAOD::MissingET *METCand = Evt->missingET();
  TLorentzVector miss(METCand->mpx(),METCand->mpy(),0,METCand->met());

  float dvalue=0;
  TLorentzVector jet1(dvalue,dvalue,dvalue,dvalue);
  if (njet>=1) jet1 = vecjet.at(0)->p4();
  TLorentzVector jet2(dvalue,dvalue,dvalue,dvalue);
  if (njet>=2) jet2 = vecjet.at(1)->p4();
  TLorentzVector SRjet1(dvalue,dvalue,dvalue,dvalue);
  if (nSRjet>=1) SRjet1 = vecSRjet.at(0)->p4();
  TLorentzVector SRjet2(dvalue,dvalue,dvalue,dvalue);
  if (nSRjet>=2) SRjet2 = vecSRjet.at(1)->p4();
  TLorentzVector SRjet3(dvalue,dvalue,dvalue,dvalue);
  if (nSRjet>=3) SRjet3 = vecSRjet.at(2)->p4();
  TLorentzVector muon1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=1) muon1 = vecmuon.at(0)->p4();
  // TLorentzVector muon2(dvalue,dvalue,dvalue,dvalue);
  // if (nmuon>=2) muon2 = vecmuon.at(1)->p4();
  // TLorentzVector muon3(dvalue,dvalue,dvalue,dvalue);
  // if (nmuon>=3) muon3 = vecmuon.at(2)->p4();
  TLorentzVector ele1(dvalue,dvalue,dvalue,dvalue);
  if (nele>=1) ele1 = vecele.at(0)->p4();
  TLorentzVector ele2(dvalue,dvalue,dvalue,dvalue);
  if (nele>=2) ele2 = vecele.at(1)->p4();
  TLorentzVector lep1(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=1) lep1 = std::get<0>(veclep.at(0))->p4(); 
  TLorentzVector lep2(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=2) lep2 = std::get<0>(veclep.at(1))->p4();
  TLorentzVector lep3(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=3) lep3 = std::get<0>(veclep.at(2))->p4();
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

  DEBUGclass("nmuon:%i nele:%i njet:%i",nmuon,nele,njet);

  float Zmass = 91187.6; // MeV
  float Wmass = 80377; // MeV
  TLorentzVector up(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector u3(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector up_cand(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um_cand(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector u3_cand(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p==2 && nmuon_m==1) {
    float M_up1um1 = (up1+um1).M();
    float M_up2um1 = (up2+um1).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up2um1-Zmass)){
      u3 = up1; up=up2; um=um1; 
      u3_cand = up2; up_cand=up1; um_cand=um1; 
    }
    if (abs(M_up1um1-Zmass)<=abs(M_up2um1-Zmass)) {
      u3 = up2; up=up1; um=um1;
      u3_cand = up1; up_cand=up2; um_cand=um1; 
    }
  }
  if (nmuon_p==1 && nmuon_m==2) {
    float M_up1um1 = (up1+um1).M();
    float M_up1um2 = (up1+um2).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up1um2-Zmass)) {
      u3 = um1; up=up1; um=um2;
      u3_cand = um2; up_cand=up1; um_cand=um1; 
    }
    if (abs(M_up1um1-Zmass)<=abs(M_up1um2-Zmass)) {
      u3 = um2; up=up1; um=um1;
      u3_cand = um1; up_cand=up1; um_cand=um2; 
    }
  }
  DEBUGclass("up pt:%f um pt:%f u3 pt:%f",up.Pt(),um.Pt(),u3.Pt());

  if (nmuon_p==1 && nmuon_m==1){
    up=up1;um=um1;
  }

  
  std::vector<TLorentzVector> vec_Zlep;
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {vec_Zlep.push_back(up);vec_Zlep.push_back(um);}
  if(nmuon_p==1 && nmuon_m==1 && nele==1) {vec_Zlep.push_back(up);vec_Zlep.push_back(um);}
  if(nele_p>=1 && nele_m>=1 && nmuon>=1) {vec_Zlep.push_back(ep);vec_Zlep.push_back(em);}
  std::sort(vec_Zlep.begin(), vec_Zlep.end(), cmp_pt_TLorentzVector );

  TLorentzVector Hlep(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector Vlep(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector Zlep1(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector Zlep2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector ZBoson(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector ZBoson_cand(dvalue,dvalue,dvalue,dvalue);
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {Hlep = u3; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;Vlep = ZBoson; ZBoson_cand=up_cand+um_cand;}
  if(nmuon_p==1 && nmuon_m==1 && nele==1) {Hlep = ele1; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;Vlep = ZBoson;}
  if(nele_p>=1 && nele_m>=1 && nmuon>=1) {Hlep = muon1; Zlep1=vec_Zlep.at(0); Zlep2=vec_Zlep.at(1); ZBoson = Zlep1+Zlep2;Vlep = ZBoson;}
  if(nlep==2) {Hlep = lep2; Vlep = lep1;}
  if(nmuon==1 && nele==0) {Vlep = lep1;}

  // TLorentzVector SRjet1_l2(dvalue,dvalue,dvalue,dvalue);
  // TLorentzVector SRjet2_l2(dvalue,dvalue,dvalue,dvalue);
  // TLorentzVector l2Wjj(dvalue,dvalue,dvalue,dvalue);
  // TLorentzVector SRjet1_l1(dvalue,dvalue,dvalue,dvalue);
  // TLorentzVector SRjet2_l1(dvalue,dvalue,dvalue,dvalue);
  // TLorentzVector l1Wjj(dvalue,dvalue,dvalue,dvalue);
  // int Wjj_count = 0;
  // if(nlep==2){
  //   auto cmp_lep2_dR = [lep2](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  //   { 
  //     return a->p4().DeltaR(lep2) < b->p4().DeltaR(lep2);
  //   };
  //   std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_lep2_dR );
  //   if (nSRjet>=1) SRjet1_l2 = vecSRjet.at(0)->p4();
  //   if (nSRjet>=2) SRjet2_l2 = vecSRjet.at(1)->p4();
  //   if (nSRjet>=2) l2Wjj = SRjet1_l2+SRjet2_l2;

  //   auto cmp_lep1_dR = [lep1](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  //   { 
  //     return a->p4().DeltaR(lep1) < b->p4().DeltaR(lep1);
  //   };
  //   std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_lep1_dR );
  //   if (nSRjet>=1) SRjet1_l1 = vecSRjet.at(0)->p4();
  //   if (nSRjet>=2) SRjet2_l1 = vecSRjet.at(1)->p4();
  //   if (nSRjet>=2) l1Wjj = SRjet1_l1+SRjet2_l1;

  //   int l1_flag =0;
  //   int l2_flag =0;
  //   if(abs(l1Wjj.M()-Wmass)/1000<20) l1_flag=1;
  //   if(abs(l2Wjj.M()-Wmass)/1000<20) l2_flag=1;
  //   if(l1_flag==1) {Hlep = lep1; Vlep = lep2;}
  //   if(l2_flag==1) {Hlep = lep2; Vlep = lep1;}
  //   if(l1_flag==1 && l2_flag==1) {Hlep = lep2; Vlep = lep1;}
  //   Wjj_count = l1_flag + l2_flag;
  // }


  TLorentzVector SRjet1_Hl(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector SRjet2_Hl(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector HWjj(dvalue,dvalue,dvalue,dvalue);
  auto cmp_Hlep_dR = [Hlep](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  { 
    return a->p4().DeltaR(Hlep) < b->p4().DeltaR(Hlep);
  };
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_Hlep_dR );
  if (nSRjet>=1) SRjet1_Hl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Hl = vecSRjet.at(1)->p4();
  if (nSRjet>=2) HWjj = SRjet1_Hl+SRjet2_Hl;

  TLorentzVector SRjet1_Vl(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector SRjet2_Vl(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector VWjj(dvalue,dvalue,dvalue,dvalue);
  auto cmp_Vlep_dR = [Vlep](const xAOD::Jet* a, const xAOD::Jet* b) -> bool
  { 
    return a->p4().DeltaR(Vlep) < b->p4().DeltaR(Vlep);
  };
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_Vlep_dR );
  if (nSRjet>=1) SRjet1_Vl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Vl = vecSRjet.at(1)->p4();
  if (nSRjet>=2) VWjj = SRjet1_Vl+SRjet2_Vl;

  // std::vector<TLorentzVector> vec_Hfatjet_cand;
  // vec_Hfatjet_cand.push_back(jet1);vec_Hfatjet_cand.push_back(jet2);vec_Hfatjet_cand.push_back(HWjj);
  // auto cmp_Wmass_dM = [Wmass](TLorentzVector a, TLorentzVector b) -> bool
  // { 
  //   return abs(a.M()-Wmass) < abs(b.M()-Wmass);
  // };
  // std::sort(vec_Hfatjet_cand.begin(), vec_Hfatjet_cand.end(), cmp_Wmass_dM );
  // TLorentzVector Hfatjet = vec_Hfatjet_cand.at(0);
  // if(nele>=1 && nSRjet>=2) {Hfatjet=HWjj;}

  int swap_flag=0;
  if (nSRjet==1){
    if (nlep==2){
      if(SRjet1_Vl.DeltaR(Vlep)<SRjet1_Hl.DeltaR(Hlep)){std::swap(Vlep,Hlep);swap_flag=1;}
    }
  }

  if (nSRjet>=2){
    if (nlep==2){
      int Hl_flag =0;
      int Vl_flag =0;
      if(SRjet2_Hl.DeltaR(Hlep)<2) Hl_flag=1;
      if(SRjet2_Vl.DeltaR(Vlep)<2) Vl_flag=1;
      if(Hl_flag==0 && Vl_flag==1) {std::swap(Vlep,Hlep);swap_flag=1;}
    }
  }

  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_Hlep_dR );
  if (nSRjet>=1) SRjet1_Hl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Hl = vecSRjet.at(1)->p4();
  if (nSRjet>=2 && SRjet2_Hl.DeltaR(Hlep) < 2) HWjj = SRjet1_Hl+SRjet2_Hl;

  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_Vlep_dR );
  if (nSRjet>=1) SRjet1_Vl = vecSRjet.at(0)->p4();
  if (nSRjet>=2) SRjet2_Vl = vecSRjet.at(1)->p4();
  if (nSRjet>=2 && SRjet2_Vl.DeltaR(Vlep) < 2) VWjj = SRjet1_Vl+SRjet2_Vl;


  TLorentzVector all_vis(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector HBoson(dvalue,dvalue,dvalue,dvalue);
  if(HWjj.Pt()!=0){
    if(nlep>=3) {HBoson = HWjj+Hlep; all_vis = HBoson+ZBoson;}
    if(nlep==2) {HBoson = HWjj+Hlep; all_vis = HBoson+Vlep;}
  }

  float sumPt_lep=0;
  float sumPt_ZHl=0;
  float sumPt_VH=0;
  if(nlep>=3) {
    sumPt_lep=Hlep.Pt()+Zlep1.Pt()+Zlep2.Pt(); 
    sumPt_ZHl=Hlep.Pt()+ZBoson.Pt();
    if(HWjj.Pt()!=0) sumPt_VH=sumPt_ZHl+HWjj.Pt();
  }
  if(nlep==2)  {
    sumPt_lep=Hlep.Pt()+Vlep.Pt();
    if(HWjj.Pt()!=0) sumPt_VH=sumPt_lep+HWjj.Pt();
  }


  int Vlep_charge = 0;
  if (nlep>=1) Vlep_charge = std::get<1>(veclep.at(0));
  int Hlep_charge = 0;
  if (nlep>=2) Hlep_charge = std::get<1>(veclep.at(1));

  //Interested_obj1
  TLorentzVector interested_obj1(dvalue,dvalue,dvalue,dvalue);
  switch (finterested_obj1) {
    case Interested_obj1::miss: 
        interested_obj1 = miss;
        break;
    case Interested_obj1::lep1: 
        interested_obj1 = lep1;
        break;
    case Interested_obj1::lep2: 
        interested_obj1 = lep2;
        break;
    case Interested_obj1::lep3: 
        interested_obj1 = lep3;
        break;
    case Interested_obj1::SRjet1: 
        interested_obj1 = SRjet1;
        break;
    case Interested_obj1::SRjet2: 
        interested_obj1 = SRjet2;
        break;
    case Interested_obj1::SRjet3: 
        interested_obj1 = SRjet3;
        break;
    case Interested_obj1::jet1: 
        interested_obj1 = jet1;
        break;
    case Interested_obj1::Hlep: 
        interested_obj1 = Hlep;
        break;
    case Interested_obj1::Vlep: 
        interested_obj1 = Vlep;
        break;
    case Interested_obj1::Zlep1: 
        interested_obj1 = Zlep1;
        break;
    case Interested_obj1::Zlep2: 
        interested_obj1 = Zlep2;
        break;
    case Interested_obj1::ZBoson: 
        interested_obj1 = ZBoson;
        break;
    case Interested_obj1::up_cand: 
        interested_obj1 = up_cand;
        break;
    case Interested_obj1::um_cand: 
        interested_obj1 = um_cand;
        break;
    case Interested_obj1::ZBoson_cand: 
        interested_obj1 = ZBoson_cand;
        break;
    case Interested_obj1::u3_cand: 
        interested_obj1 = u3_cand;
        break;
    case Interested_obj1::HWjj: 
        interested_obj1 = HWjj;
        break;
    case Interested_obj1::SRjet1_Hl: 
        interested_obj1 = SRjet1_Hl;
        break;
    case Interested_obj1::SRjet2_Hl: 
        interested_obj1 = SRjet2_Hl;
        break;
    case Interested_obj1::VWjj: 
        interested_obj1 = VWjj;
        break;
    case Interested_obj1::SRjet1_Vl: 
        interested_obj1 = SRjet1_Vl;
        break;
    case Interested_obj1::SRjet2_Vl: 
        interested_obj1 = SRjet2_Vl;
        break;
    case Interested_obj1::HBoson: 
        interested_obj1 = HBoson;
        break;
    case Interested_obj1::all_vis: 
        interested_obj1 = all_vis;
        break;
    default:
      break;
  }
  //Interested_obj2
  TLorentzVector interested_obj2(dvalue,dvalue,dvalue,dvalue);
  switch (finterested_obj2) {
    case Interested_obj2::miss: 
        interested_obj2 = miss;
        break;
    case Interested_obj2::lep1: 
        interested_obj2 = lep1;
        break;
    case Interested_obj2::lep2: 
        interested_obj2 = lep2;
        break;
    case Interested_obj2::lep3: 
        interested_obj2 = lep3;
        break;
    case Interested_obj2::SRjet1: 
        interested_obj2 = SRjet1;
        break;
    case Interested_obj2::SRjet2: 
        interested_obj2 = SRjet2;
        break;
    case Interested_obj2::SRjet3: 
        interested_obj2 = SRjet3;
        break;
    case Interested_obj2::jet1: 
        interested_obj2 = jet1;
        break;
    case Interested_obj2::Hlep: 
        interested_obj2 = Hlep;
        break;
    case Interested_obj2::Vlep: 
        interested_obj2 = Vlep;
        break;
    case Interested_obj2::Zlep1: 
        interested_obj2 = Zlep1;
        break;
    case Interested_obj2::Zlep2: 
        interested_obj2 = Zlep2;
        break;
    case Interested_obj2::ZBoson: 
        interested_obj2 = ZBoson;
        break;
    case Interested_obj2::up_cand: 
        interested_obj2 = up_cand;
        break;
    case Interested_obj2::um_cand: 
        interested_obj2 = um_cand;
        break;
    case Interested_obj2::ZBoson_cand: 
        interested_obj2 = ZBoson_cand;
        break;
    case Interested_obj2::u3_cand: 
        interested_obj2 = u3_cand;
        break;
    case Interested_obj2::HWjj: 
        interested_obj2 = HWjj;
        break;
    case Interested_obj2::SRjet1_Hl: 
        interested_obj2 = SRjet1_Hl;
        break;
    case Interested_obj2::SRjet2_Hl: 
        interested_obj2 = SRjet2_Hl;
        break;
    case Interested_obj2::VWjj: 
        interested_obj2 = VWjj;
        break;
    case Interested_obj2::SRjet1_Vl: 
        interested_obj2 = SRjet1_Vl;
        break;
    case Interested_obj2::SRjet2_Vl: 
        interested_obj2 = SRjet2_Vl;
        break;
    case Interested_obj2::HBoson: 
        interested_obj2 = HBoson;
        break;
    case Interested_obj2::all_vis: 
        interested_obj2 = all_vis;
        break;
    default:
      break;
  }

  float rval=-99;
  if(return_mode==0) {
    switch (fnumber_variable) {
      case Number_variable::njet: 
        rval = njet;
        break;
      case Number_variable::nSRjet: 
        rval = nSRjet;
        break;
      case Number_variable::nmuon: 
        rval = nmuon;
        break;
      case Number_variable::nmuon_p: 
        rval = nmuon_p;
        break;
      case Number_variable::nmuon_m: 
        rval = nmuon_m;
        break;
      case Number_variable::nele: 
        rval = nele;
        break;
      case Number_variable::nele_p: 
        rval = nele_p;
        break;
      case Number_variable::nele_m: 
        rval = nele_m;
        break;
      case Number_variable::nlep: 
        rval = nlep;
        break;
      case Number_variable::sumPt_SRjet: 
        rval = sumPt_SRjet/1000;
        break;
      case Number_variable::sumPt_lep: 
        rval = sumPt_lep/1000;
        break;
      case Number_variable::sumPt_ZHl: 
        rval = sumPt_ZHl/1000;
        break;
      case Number_variable::sumPt_VH: 
        rval = sumPt_VH/1000;
        break;
      case Number_variable::swap_flag: 
        rval = swap_flag;
        break;
      default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in NumberObservable :: unrecognised interested_variable. Check your configuration of this observable.");
    }
  }
  if(return_mode==1) {
    switch (finterested_variable) {
      case Interested_variable::pt: 
        rval = interested_obj1.Pt()/1000;
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::eta: 
        rval = interested_obj1.Eta();
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::phi: 
        rval = interested_obj1.Phi();
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::e: 
        rval = interested_obj1.E()/1000;
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::m: 
        rval = interested_obj1.M()/1000;
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::mT: 
        rval = sqrt(2*sqrt(interested_obj1.M()* interested_obj1.M()+ interested_obj1.Pt()* interested_obj1.Pt())*miss.E()*(1-cos(interested_obj1.DeltaPhi(miss))))/1000;
        if (interested_obj1.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::charge: 
        if (finterested_obj1==Interested_obj1::Hlep) rval = Hlep_charge;
        if (finterested_obj1==Interested_obj1::Vlep) rval = Vlep_charge;
        break;
      default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in KineticObservable :: unrecognised interested_variable. Check your configuration of this observable.");
    }
  }
  if(return_mode==2){
    switch (finterested_variable) {
      case Interested_variable::dR: 
        rval = interested_obj1.DeltaR(interested_obj2);
        if (interested_obj1.Pt()==dvalue || interested_obj2.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::dEta: 
        rval = std::abs(interested_obj1.Eta()-interested_obj2.Eta());
        if (interested_obj1.Pt()==dvalue || interested_obj2.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::dPhi: 
        rval = interested_obj1.DeltaPhi(interested_obj2);
        if (interested_obj1.Pt()==dvalue || interested_obj2.Pt()==dvalue) rval = 0.0;
        break;
      case Interested_variable::dPt: 
        rval = std::abs(interested_obj1.Pt()-interested_obj2.Pt())/1000;
        if (interested_obj1.Pt()==dvalue || interested_obj2.Pt()==dvalue) rval = 0.0;
        break;
      default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in CompositeObservable :: unrecognised interested_variable. Check your configuration of this observable.");
    }
  }
  return rval;
}
//______________________________________________________________________________________________
// getClone override (so we don't have to rely on root streamer)
// TQObservable* lvqqObservable::getClone() const  {
//   // retrieve a clone of this observable
//   TQObservable* obs = NULL;
//   if(this->hasExpression()){
//     obs = this->tryCreateInstanceVirtual(this->getExpression());
//   }
  // if(!obs){
    // obs = (TQObservable*)(this->Clone()); DON'T USE ROOT STREAMER, INSTEAD USE COPY constructor
  //   obs = new lvqqObservable(*this);
  // }
//   if(obs->isInitialized()) obs->finalize();
//   return obs;
// }

//______________________________________________________________________________________________
bool lvqqObservable::initializeSelf(){
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

lvqqObservable::lvqqObservable(const TString& name,const int number_variable):TQEventObservable(name)
{
  fnumber_variable=static_cast<Number_variable>(number_variable);
  return_mode=0;
}

lvqqObservable::lvqqObservable(const TString& name,const int interested_obj1, const int interested_variable):TQEventObservable(name)
{
  finterested_obj1=static_cast<Interested_obj1>(interested_obj1);
  finterested_variable=static_cast<Interested_variable>(interested_variable);
  return_mode=1;
}

lvqqObservable::lvqqObservable(const TString& name,const int interested_obj1,const int interested_obj2, const int interested_variable):TQEventObservable(name)
{
  finterested_obj1=static_cast<Interested_obj1>(interested_obj1);
  finterested_obj2=static_cast<Interested_obj2>(interested_obj2);
  finterested_variable=static_cast<Interested_variable>(interested_variable);
  return_mode=2;
}

bool lvqqObservable :: cmp_pt_IParticle (std::tuple<const xAOD::IParticle*, int> a,std::tuple<const xAOD::IParticle*, int> b)
{
    return std::get<0>(a)->pt() > std::get<0>(b)->pt();
}
bool lvqqObservable :: cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b)
{
    return a->pt() > b->pt();
}
bool lvqqObservable :: cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b)
{
    return a->pt() > b->pt();
}
bool lvqqObservable :: cmp_pt_TLorentzVector (TLorentzVector a,TLorentzVector b)
{
    return a.Pt() > b.Pt();
}
bool lvqqObservable :: cmp_pt_Jet (const xAOD::Jet* a,const xAOD::Jet* b)
{
    return a->pt() > b->pt();
}




