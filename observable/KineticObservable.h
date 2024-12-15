#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

#ifndef __KineticObservable__
#define __KineticObservable__

using namespace std;
// which lepton to check and what to check for
enum Interested_Obj {
  miss,
  Hlep,
  VWlep,
  Zlep1,
  Zlep2,
  ZBoson,
  Hfatjet,
  HBoson,
  all_vis,
  jet1,
  l1Wjj,
  SRjet1_l1,
  SRjet2_l1,
  l2Wjj,
  SRjet1_l2,
  SRjet2_l2,
  HlWjj,
  SRjet1_Hl,
  SRjet2_Hl,
  VlWjj,
  SRjet1_Vl,
  SRjet2_Vl,
};

// type of analysis being performed
enum Interested_Variable { pt, eta, phi, e, m, mT, charge//, HWnu_pz_real, HWnu_pz 
};

class KineticObservable : public TQEventObservable {

private:
  Interested_Obj finterested_obj;

  Interested_Variable finterested_variable;

protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const
  // functions the "const" keyword ensures that const containers can be
  // retrieved for example, use
  mutable xAOD::CompositeParticleContainer const *mCand = 0;

public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;
  TString mCandName = "";
  // getClone override (so we don't have to rely on root streamer)
  // TQObservable* getClone() const override;

public:
  // default constructor
  KineticObservable();
  // copy constructor
  KineticObservable(const KineticObservable &obs);
  // nominal constructor
  KineticObservable(const TString &name, const int interested_obj,
                    const int interested_variable);
  virtual ~KineticObservable();
  ClassDefOverride(KineticObservable, 1);

private:
  // class Cmp_pt_KO {
  //   public:
  //     bool operator() (const xAOD::IParticle* a,const xAOD::IParticle* b) {
  //     // something
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (const xAOD::Muon* a,const xAOD::Muon* b) { //
  //     something
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (const xAOD::Electron* a,const xAOD::Electron* b) { //
  //     something
  //         return a->pt() > b->pt();
  //     }
  //     bool operator() (TLorentzVector a,TLorentzVector b) { // something
  //         return a.Pt() > b.Pt();
  //     }
  //     bool operator() (const xAOD::Jet* a,const xAOD::Jet* b) { // something
  //         return a->pt() > b->pt();
  //     }
  // } cmp_pt_KO;
  static bool cmp_pt_IParticle(std::tuple<const xAOD::IParticle*, int> a,
                               std::tuple<const xAOD::IParticle*, int> b);
  static bool cmp_pt_Muon(const xAOD::Muon *a, const xAOD::Muon *b);
  static bool cmp_pt_Electron(const xAOD::Electron *a, const xAOD::Electron *b);
  static bool cmp_pt_TLorentzVector(TLorentzVector a, TLorentzVector b);
  static bool cmp_pt_Jet(const xAOD::Jet *a, const xAOD::Jet *b);
  

  // pair<bool, float> get_HWnuPt(TLorentzVector HWlep,
  //                              TLorentzVector miss) const {
  //   float Wmass = 80377;
  //   float Wpz_square = pow(miss.E() + HWlep.E(), 2) - Wmass * Wmass -
  //                      pow(miss.Px() + HWlep.Px(), 2) -
  //                      pow(miss.Py() + HWlep.Py(), 2);
  //   bool HWnu_pz_real = false;
  //   float HWnu_pz = 0;
  //   if (Wpz_square > 0) {
  //     HWnu_pz_real = true;
  //     auto HWnu_pz_1 = -HWlep.Pz() + sqrt(Wpz_square);
  //     auto HWnu_pz_2 = -HWlep.Pz() - sqrt(Wpz_square);
  //     if (abs(HWnu_pz_1) < abs(HWnu_pz_2))
  //       HWnu_pz = HWnu_pz_1;
  //     else
  //       HWnu_pz = HWnu_pz_2;
  //   }
  //   pair<bool, float> rval = {HWnu_pz_real, HWnu_pz};
  //   return rval;
  // }
};
#endif