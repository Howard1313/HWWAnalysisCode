#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

#ifndef __CompositeObservable__
#define __CompositeObservable__

enum class Interested_Obj1 {
  miss,
  jet1,
  jet2,
  muon1,
  muon2,
  ele1,
  up,
  um,
  u3,
  ep,
  em,
  zero,
  u1j1,
  u3j1
};

enum class Interested_Obj2 {
  miss,
  jet1,
  jet2,
  muon1,
  muon2,
  ele1,
  up,
  um,
  u3,
  ep,
  em,
  zero
};

enum class Interested_CompoVariable {
  dR,
  M,
  Pt,
  mT
};

// type of analysis being performed


class CompositeObservable : public TQEventObservable {

private:

 
  Interested_Obj1 finterested_obj1;
  Interested_Obj2 finterested_obj2;

  Interested_CompoVariable finterested_variable;

protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  mutable xAOD::CompositeParticleContainer const * mCand = 0;




public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;
  TString mCandName = "";
  // getClone override (so we don't have to rely on root streamer)
  // TQObservable* getClone() const override;

public:
  // default constructor
  CompositeObservable();
  // copy constructor
  CompositeObservable(const CompositeObservable& obs);
  // nominal constructor
  CompositeObservable(const TString& name, const int interested_obj1, const int interested_obj2, const int interested_variable);
  virtual ~CompositeObservable();
  ClassDefOverride(CompositeObservable, 1);

private:
  
  // class Cmp_pt_KO {
  //   public:
  //     bool operator() (const xAOD::IParticle* a,const xAOD::IParticle* b) { // something 
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (const xAOD::Muon* a,const xAOD::Muon* b) { // something 
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (const xAOD::Electron* a,const xAOD::Electron* b) { // something 
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (TLorentzVector a,TLorentzVector b) { // something 
  //         return a.Pt() > b.Pt();
  //     }
  //     bool operator() (const xAOD::Jet* a,const xAOD::Jet* b) { // something 
  //         return a->pt() > b->pt();
  //     }
  // } cmp_pt_KO;
  static bool cmp_pt_IParticle (const xAOD::IParticle* a,const xAOD::IParticle* b);
  static bool cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b);
  static bool cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b);
  static bool cmp_pt_TLorentzVector (TLorentzVector a,TLorentzVector b);
  static bool cmp_pt_Jet (const xAOD::Jet* a,const xAOD::Jet* b);

  float get_mT (TLorentzVector vis, TLorentzVector neutrino) const {
    auto ET=sqrt(vis.M()* vis.M()+ vis.Pt()* vis.Pt());
    return sqrt(2*ET*neutrino.E()*(1-cos(vis.DeltaPhi(neutrino))));
  }
};
#endif