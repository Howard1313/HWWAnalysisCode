from QFramework import TQTreeObservable, INFO, ERROR
import ROOT
from HWWAnalysisCode import KineticObservable

class Interested_Obj:
  miss =0
  Hlep =1
  VWlep =2
  Zlep1 =3
  Zlep2 =4
  ZBoson =5
  Hfatjet =6
  HBoson =7
  all_vis =8
  jet1 = 9
  l1Wjj = 10
  SRjet1_l1 = 11
  SRjet2_l1 = 12
  l2Wjj = 13
  SRjet1_l2 = 14
  SRjet2_l2 = 15
  HlWjj = 16
  SRjet1_Hl = 17
  SRjet2_Hl = 18
  VlWjj = 19
  SRjet1_Vl = 20
  SRjet2_Vl = 21

class Interested_Variable:
  pt =0
  eta =1 
  phi =2 
  e =3
  m =4
  mT =5
  charge =6
  # HWnu_pz_real =7
  # HWnu_pz =8

def addObservables(config):
  from QFramework import TQObservable,INFO,ERROR,BREAK,WARN

  
  # try:
  #   from HWWAnalysisCode import KineticObservable
  # except Exception as error:
  #   ERROR("Couldn't import KineticObservable.h module!\n"+"Message from python:\n"+str(error))
  #   return False


  INFO("adding KineticObservable")
  #=== The integers must match the correct modes inside HWWLeptonIDObservable.cxx
  MET = KineticObservable("MET", Interested_Obj.miss, Interested_Variable.e)
  if not TQObservable.addObservable(MET): return False

  miss_phi = KineticObservable("miss_phi", Interested_Obj.miss, Interested_Variable.phi)
  if not TQObservable.addObservable(miss_phi): return False

  
  Hlep_pt = KineticObservable("Hlep_pt", Interested_Obj.Hlep, Interested_Variable.pt)
  if not TQObservable.addObservable(Hlep_pt): return False

  Hlep_eta = KineticObservable("Hlep_eta", Interested_Obj.Hlep, Interested_Variable.eta)   
  if not TQObservable.addObservable(Hlep_eta): return False

  Hlep_phi = KineticObservable("Hlep_phi", Interested_Obj.Hlep, Interested_Variable.phi)
  if not TQObservable.addObservable(Hlep_phi): return False

  Hlep_e = KineticObservable("Hlep_e", Interested_Obj.Hlep, Interested_Variable.e)
  if not TQObservable.addObservable(Hlep_e): return False

  Hlep_charge = KineticObservable("Hlep_charge", Interested_Obj.Hlep, Interested_Variable.charge)
  if not TQObservable.addObservable(Hlep_charge): return False


  VWlep_pt = KineticObservable("VWlep_pt", Interested_Obj.VWlep, Interested_Variable.pt)
  if not TQObservable.addObservable(VWlep_pt): return False

  VWlep_eta = KineticObservable("VWlep_eta", Interested_Obj.VWlep, Interested_Variable.eta)   
  if not TQObservable.addObservable(VWlep_eta): return False

  VWlep_phi = KineticObservable("VWlep_phi", Interested_Obj.VWlep, Interested_Variable.phi)
  if not TQObservable.addObservable(VWlep_phi): return False

  VWlep_e = KineticObservable("VWlep_e", Interested_Obj.VWlep, Interested_Variable.e)
  if not TQObservable.addObservable(VWlep_e): return False

  VWlep_charge = KineticObservable("VWlep_charge", Interested_Obj.VWlep, Interested_Variable.charge)
  if not TQObservable.addObservable(VWlep_charge): return False

  
  Zlep1_pt = KineticObservable("Zlep1_pt", Interested_Obj.Zlep1, Interested_Variable.pt)
  if not TQObservable.addObservable(Zlep1_pt): return False

  Zlep1_eta = KineticObservable("Zlep1_eta", Interested_Obj.Zlep1, Interested_Variable.eta)   
  if not TQObservable.addObservable(Zlep1_eta): return False

  Zlep1_phi = KineticObservable("Zlep1_phi", Interested_Obj.Zlep1, Interested_Variable.phi)
  if not TQObservable.addObservable(Zlep1_phi): return False

  Zlep1_e = KineticObservable("Zlep1_e", Interested_Obj.Zlep1, Interested_Variable.e)
  if not TQObservable.addObservable(Zlep1_e): return False

  
  Zlep2_pt = KineticObservable("Zlep2_pt", Interested_Obj.Zlep2, Interested_Variable.pt)
  if not TQObservable.addObservable(Zlep2_pt): return False

  Zlep2_eta = KineticObservable("Zlep2_eta", Interested_Obj.Zlep2, Interested_Variable.eta)   
  if not TQObservable.addObservable(Zlep2_eta): return False

  Zlep2_phi = KineticObservable("Zlep2_phi", Interested_Obj.Zlep2, Interested_Variable.phi)
  if not TQObservable.addObservable(Zlep2_phi): return False

  Zlep2_e = KineticObservable("Zlep2_e", Interested_Obj.Zlep2, Interested_Variable.e)
  if not TQObservable.addObservable(Zlep2_e): return False

  
  ZBoson_pt = KineticObservable("ZBoson_pt", Interested_Obj.ZBoson, Interested_Variable.pt)
  if not TQObservable.addObservable(ZBoson_pt): return False

  ZBoson_eta = KineticObservable("ZBoson_eta", Interested_Obj.ZBoson, Interested_Variable.eta)   
  if not TQObservable.addObservable(ZBoson_eta): return False

  ZBoson_phi = KineticObservable("ZBoson_phi", Interested_Obj.ZBoson, Interested_Variable.phi)
  if not TQObservable.addObservable(ZBoson_phi): return False

  ZBoson_e = KineticObservable("ZBoson_e", Interested_Obj.ZBoson, Interested_Variable.e)
  if not TQObservable.addObservable(ZBoson_e): return False

  ZBoson_m = KineticObservable("ZBoson_m", Interested_Obj.ZBoson, Interested_Variable.m)
  if not TQObservable.addObservable(ZBoson_m): return False

  
  Hfatjet_pt = KineticObservable("Hfatjet_pt", Interested_Obj.Hfatjet, Interested_Variable.pt)
  if not TQObservable.addObservable(Hfatjet_pt): return False

  Hfatjet_eta = KineticObservable("Hfatjet_eta", Interested_Obj.Hfatjet, Interested_Variable.eta)   
  if not TQObservable.addObservable(Hfatjet_eta): return False

  Hfatjet_phi = KineticObservable("Hfatjet_phi", Interested_Obj.Hfatjet, Interested_Variable.phi)
  if not TQObservable.addObservable(Hfatjet_phi): return False

  Hfatjet_e = KineticObservable("Hfatjet_e", Interested_Obj.Hfatjet, Interested_Variable.e)
  if not TQObservable.addObservable(Hfatjet_e): return False

  Hfatjet_m = KineticObservable("Hfatjet_m", Interested_Obj.Hfatjet, Interested_Variable.m)
  if not TQObservable.addObservable(Hfatjet_m): return False

  
  HBoson_pt = KineticObservable("HBoson_pt", Interested_Obj.HBoson, Interested_Variable.pt)
  if not TQObservable.addObservable(HBoson_pt): return False

  HBoson_eta = KineticObservable("HBoson_eta", Interested_Obj.HBoson, Interested_Variable.eta)   
  if not TQObservable.addObservable(HBoson_eta): return False

  HBoson_phi = KineticObservable("HBoson_phi", Interested_Obj.HBoson, Interested_Variable.phi)
  if not TQObservable.addObservable(HBoson_phi): return False

  HBoson_e = KineticObservable("HBoson_e", Interested_Obj.HBoson, Interested_Variable.e)
  if not TQObservable.addObservable(HBoson_e): return False

  HBoson_m = KineticObservable("HBoson_m", Interested_Obj.HBoson, Interested_Variable.m)
  if not TQObservable.addObservable(HBoson_m): return False


  all_vis_pt = KineticObservable("all_vis_pt", Interested_Obj.all_vis, Interested_Variable.pt)
  if not TQObservable.addObservable(all_vis_pt): return False

  all_vis_eta = KineticObservable("all_vis_eta", Interested_Obj.all_vis, Interested_Variable.eta)   
  if not TQObservable.addObservable(all_vis_eta): return False

  all_vis_phi = KineticObservable("all_vis_phi", Interested_Obj.all_vis, Interested_Variable.phi)
  if not TQObservable.addObservable(all_vis_phi): return False

  all_vis_e = KineticObservable("all_vis_e", Interested_Obj.all_vis, Interested_Variable.e)
  if not TQObservable.addObservable(all_vis_e): return False

  all_vis_m = KineticObservable("all_vis_m", Interested_Obj.all_vis, Interested_Variable.m)
  if not TQObservable.addObservable(all_vis_m): return False

  
  l1Wjj_pt = KineticObservable("l1Wjj_pt", Interested_Obj.l1Wjj, Interested_Variable.pt)
  if not TQObservable.addObservable(l1Wjj_pt): return False

  l1Wjj_eta = KineticObservable("l1Wjj_eta", Interested_Obj.l1Wjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(l1Wjj_eta): return False

  l1Wjj_phi = KineticObservable("l1Wjj_phi", Interested_Obj.l1Wjj, Interested_Variable.phi)
  if not TQObservable.addObservable(l1Wjj_phi): return False

  l1Wjj_e = KineticObservable("l1Wjj_e", Interested_Obj.l1Wjj, Interested_Variable.e)
  if not TQObservable.addObservable(l1Wjj_e): return False

  l1Wjj_m = KineticObservable("l1Wjj_m", Interested_Obj.l1Wjj, Interested_Variable.m)
  if not TQObservable.addObservable(l1Wjj_m): return False

  
  l2Wjj_pt = KineticObservable("l2Wjj_pt", Interested_Obj.l2Wjj, Interested_Variable.pt)
  if not TQObservable.addObservable(l2Wjj_pt): return False

  l2Wjj_eta = KineticObservable("l2Wjj_eta", Interested_Obj.l2Wjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(l2Wjj_eta): return False

  l2Wjj_phi = KineticObservable("l2Wjj_phi", Interested_Obj.l2Wjj, Interested_Variable.phi)
  if not TQObservable.addObservable(l2Wjj_phi): return False

  l2Wjj_e = KineticObservable("l2Wjj_e", Interested_Obj.l2Wjj, Interested_Variable.e)
  if not TQObservable.addObservable(l2Wjj_e): return False

  l2Wjj_m = KineticObservable("l2Wjj_m", Interested_Obj.l2Wjj, Interested_Variable.m)
  if not TQObservable.addObservable(l2Wjj_m): return False

  
  HlWjj_pt = KineticObservable("HlWjj_pt", Interested_Obj.HlWjj, Interested_Variable.pt)
  if not TQObservable.addObservable(HlWjj_pt): return False

  HlWjj_eta = KineticObservable("HlWjj_eta", Interested_Obj.HlWjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(HlWjj_eta): return False

  HlWjj_phi = KineticObservable("HlWjj_phi", Interested_Obj.HlWjj, Interested_Variable.phi)
  if not TQObservable.addObservable(HlWjj_phi): return False

  HlWjj_e = KineticObservable("HlWjj_e", Interested_Obj.HlWjj, Interested_Variable.e)
  if not TQObservable.addObservable(HlWjj_e): return False

  HlWjj_m = KineticObservable("HlWjj_m", Interested_Obj.HlWjj, Interested_Variable.m)
  if not TQObservable.addObservable(HlWjj_m): return False

  
  VlWjj_pt = KineticObservable("VlWjj_pt", Interested_Obj.VlWjj, Interested_Variable.pt)
  if not TQObservable.addObservable(VlWjj_pt): return False

  VlWjj_eta = KineticObservable("VlWjj_eta", Interested_Obj.VlWjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(VlWjj_eta): return False

  VlWjj_phi = KineticObservable("VlWjj_phi", Interested_Obj.VlWjj, Interested_Variable.phi)
  if not TQObservable.addObservable(VlWjj_phi): return False

  VlWjj_e = KineticObservable("VlWjj_e", Interested_Obj.VlWjj, Interested_Variable.e)
  if not TQObservable.addObservable(VlWjj_e): return False

  VlWjj_m = KineticObservable("VlWjj_m", Interested_Obj.VlWjj, Interested_Variable.m)
  if not TQObservable.addObservable(VlWjj_m): return False


  
  SRjet1_l1_pt = KineticObservable("SRjet1_l1_pt", Interested_Obj.SRjet1_l1, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_l1_pt): return False

  SRjet1_l1_eta = KineticObservable("SRjet1_l1_eta", Interested_Obj.SRjet1_l1, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_l1_eta): return False

  SRjet1_l1_phi = KineticObservable("SRjet1_l1_phi", Interested_Obj.SRjet1_l1, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet1_l1_phi): return False

  SRjet1_l1_e = KineticObservable("SRjet1_l1_e", Interested_Obj.SRjet1_l1, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_l1_e): return False

  SRjet1_l1_m = KineticObservable("SRjet1_l1_m", Interested_Obj.SRjet1_l1, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_l1_m): return False


  SRjet2_l1_pt = KineticObservable("SRjet2_l1_pt", Interested_Obj.SRjet2_l1, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_l1_pt): return False

  SRjet2_l1_eta = KineticObservable("SRjet2_l1_eta", Interested_Obj.SRjet2_l1, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_l1_eta): return False

  SRjet2_l1_phi = KineticObservable("SRjet2_l1_phi", Interested_Obj.SRjet2_l1, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet2_l1_phi): return False

  SRjet2_l1_e = KineticObservable("SRjet2_l1_e", Interested_Obj.SRjet2_l1, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_l1_e): return False

  SRjet2_l1_m = KineticObservable("SRjet2_l1_m", Interested_Obj.SRjet2_l1, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_l1_m): return False

  
  SRjet1_l2_pt = KineticObservable("SRjet1_l2_pt", Interested_Obj.SRjet1_l2, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_l2_pt): return False

  SRjet1_l2_eta = KineticObservable("SRjet1_l2_eta", Interested_Obj.SRjet1_l2, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_l2_eta): return False

  SRjet1_l2_phi = KineticObservable("SRjet1_l2_phi", Interested_Obj.SRjet1_l2, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet1_l2_phi): return False

  SRjet1_l2_e = KineticObservable("SRjet1_l2_e", Interested_Obj.SRjet1_l2, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_l2_e): return False

  SRjet1_l2_m = KineticObservable("SRjet1_l2_m", Interested_Obj.SRjet1_l2, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_l2_m): return False
    

  SRjet2_l2_pt = KineticObservable("SRjet2_l2_pt", Interested_Obj.SRjet2_l2, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_l2_pt): return False

  SRjet2_l2_eta = KineticObservable("SRjet2_l2_eta", Interested_Obj.SRjet2_l2, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_l2_eta): return False

  SRjet2_l2_phi = KineticObservable("SRjet2_l2_phi", Interested_Obj.SRjet2_l2, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet2_l2_phi): return False

  SRjet2_l2_e = KineticObservable("SRjet2_l2_e", Interested_Obj.SRjet2_l2, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_l2_e): return False

  SRjet2_l2_m = KineticObservable("SRjet2_l2_m", Interested_Obj.SRjet2_l2, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_l2_m): return False


  SRjet1_Vl_pt = KineticObservable("SRjet1_Vl_pt", Interested_Obj.SRjet1_Vl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_Vl_pt): return False

  SRjet1_Vl_eta = KineticObservable("SRjet1_Vl_eta", Interested_Obj.SRjet1_Vl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_Vl_eta): return False

  SRjet1_Vl_phi = KineticObservable("SRjet1_Vl_phi", Interested_Obj.SRjet1_Vl, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet1_Vl_phi): return False

  SRjet1_Vl_e = KineticObservable("SRjet1_Vl_e", Interested_Obj.SRjet1_Vl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_Vl_e): return False

  SRjet1_Vl_m = KineticObservable("SRjet1_Vl_m", Interested_Obj.SRjet1_Vl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_Vl_m): return False


  SRjet2_Vl_pt = KineticObservable("SRjet2_Vl_pt", Interested_Obj.SRjet2_Vl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_Vl_pt): return False

  SRjet2_Vl_eta = KineticObservable("SRjet2_Vl_eta", Interested_Obj.SRjet2_Vl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_Vl_eta): return False

  SRjet2_Vl_phi = KineticObservable("SRjet2_Vl_phi", Interested_Obj.SRjet2_Vl, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet2_Vl_phi): return False

  SRjet2_Vl_e = KineticObservable("SRjet2_Vl_e", Interested_Obj.SRjet2_Vl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_Vl_e): return False

  SRjet2_Vl_m = KineticObservable("SRjet2_Vl_m", Interested_Obj.SRjet2_Vl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_Vl_m): return False

  SRjet1_Hl_pt = KineticObservable("SRjet1_Hl_pt", Interested_Obj.SRjet1_Hl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_Hl_pt): return False

  SRjet1_Hl_eta = KineticObservable("SRjet1_Hl_eta", Interested_Obj.SRjet1_Hl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_Hl_eta): return False

  SRjet1_Hl_phi = KineticObservable("SRjet1_Hl_phi", Interested_Obj.SRjet1_Hl, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet1_Hl_phi): return False

  SRjet1_Hl_e = KineticObservable("SRjet1_Hl_e", Interested_Obj.SRjet1_Hl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_Hl_e): return False

  SRjet1_Hl_m = KineticObservable("SRjet1_Hl_m", Interested_Obj.SRjet1_Hl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_Hl_m): return False


  SRjet2_Hl_pt = KineticObservable("SRjet2_Hl_pt", Interested_Obj.SRjet2_Hl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_Hl_pt): return False

  SRjet2_Hl_eta = KineticObservable("SRjet2_Hl_eta", Interested_Obj.SRjet2_Hl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_Hl_eta): return False

  SRjet2_Hl_phi = KineticObservable("SRjet2_Hl_phi", Interested_Obj.SRjet2_Hl, Interested_Variable.phi)
  if not TQObservable.addObservable(SRjet2_Hl_phi): return False

  SRjet2_Hl_e = KineticObservable("SRjet2_Hl_e", Interested_Obj.SRjet2_Hl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_Hl_e): return False

  SRjet2_Hl_m = KineticObservable("SRjet2_Hl_m", Interested_Obj.SRjet2_Hl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_Hl_m): return False
    
  
  Hlep_mT = KineticObservable("Hlep_mT", Interested_Obj.Hlep, Interested_Variable.mT)
  if not TQObservable.addObservable(Hlep_mT): return False
  HBoson_mT = KineticObservable("HBoson_mT", Interested_Obj.HBoson, Interested_Variable.mT)
  if not TQObservable.addObservable(HBoson_mT): return False

  return True

if __name__ == "__main__":
  print "Inside main of KineticObservable python snippet"
  if not addObservables():
    print("Couldn't add KineticObservable!")
  else:
    print("Successfully added KineticObservable")
