#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

#ifndef __lvqqObservable__
#define __lvqqObservable__

using namespace std;
// which lepton to check and what to check for
enum class Interested_obj1 {
  miss,
  lep1,
  lep2,
  lep3,
  SRjet1,
  SRjet2,
  SRjet3,
  jet1,
  Hlep,
  Vlep,
  Zlep1,
  Zlep2,
  ZBoson,
  up_cand,
  um_cand,
  ZBoson_cand,
  u3_cand,
  HWjj,
  SRjet1_Hl,
  SRjet2_Hl,
  VWjj,
  SRjet1_Vl,
  SRjet2_Vl,
  HBoson,
  all_vis
};
enum class Interested_obj2 {
miss,
  lep1,
  lep2,
  lep3,
  SRjet1,
  SRjet2,
  SRjet3,
  jet1,
  Hlep,
  Vlep,
  Zlep1,
  Zlep2,
  ZBoson,
  up_cand,
  um_cand,
  ZBoson_cand,
  u3_cand,
  HWjj,
  SRjet1_Hl,
  SRjet2_Hl,
  VWjj,
  SRjet1_Vl,
  SRjet2_Vl,
  HBoson,
  all_vis
};

// type of analysis being performed
enum class Interested_variable { pt, eta, phi, e, m, mT, charge,
  dR,
  dPhi,
  dEta,
  dPt
};

enum class Number_variable {
  njet,
  nSRjet,
  nmuon,
  nmuon_p,
  nmuon_m,
  nele,
  nele_p,
  nele_m,
  nlep,
  sumPt_SRjet,
  sumPt_lep,
  sumPt_ZHl,
  sumPt_VH,
  swap_flag
};

class lvqqObservable : public TQEventObservable {

private:
  Interested_obj1 finterested_obj1;
  Interested_obj2 finterested_obj2;

  Interested_variable finterested_variable;
  Number_variable fnumber_variable;

  int return_mode;

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
  lvqqObservable();
  // copy constructor
  lvqqObservable(const lvqqObservable &obs);
  // nominal constructor
  lvqqObservable(const TString& name, const int number_variable);
  lvqqObservable(const TString& name, const int interested_obj1,
                  const int interested_variable);

  lvqqObservable(const TString& name, const int interested_obj1, const int interested_obj2, 
                  const int interested_variable);
  
  virtual ~lvqqObservable();
  ClassDefOverride(lvqqObservable, 1);

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