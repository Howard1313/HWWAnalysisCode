from QFramework import TQTreeObservable, INFO, ERROR
import ROOT
from HWWAnalysisCode import lvqqObservable

class Interested_Obj1:
  miss = 0
  lep1 = 1
  lep2 = 2
  lep3 = 3
  SRjet1 = 4
  SRjet2 = 5
  SRjet3 = 6
  jet1 = 7
  Hlep = 8
  Vlep = 9
  Zlep1 = 10
  Zlep2 = 11
  ZBoson = 12
  up_cand = 13
  um_cand = 14
  ZBoson_cand = 15
  u3_cand = 16
  HWjj = 17
  SRjet1_Hl = 18
  SRjet2_Hl = 19
  VWjj = 20
  SRjet1_Vl = 21
  SRjet2_Vl = 22
  HBoson = 23
  all_vis = 24

class Interested_Obj2:
  miss = 0
  lep1 = 1
  lep2 = 2
  lep3 = 3
  SRjet1 = 4
  SRjet2 = 5
  SRjet3 = 6
  jet1 = 7
  Hlep = 8
  Vlep = 9
  Zlep1 = 10
  Zlep2 = 11
  ZBoson = 12
  up_cand = 13
  um_cand = 14
  ZBoson_cand = 15
  u3_cand = 16
  HWjj = 17
  SRjet1_Hl = 18
  SRjet2_Hl = 19
  VWjj = 20
  SRjet1_Vl = 21
  SRjet2_Vl = 22
  HBoson = 23
  all_vis = 24

class Interested_Variable:
  pt =0
  eta =1 
  phi =2 
  e =3
  m =4
  mT =5
  charge =6
  dR  = 7
  dPhi  = 8
  dEta  = 9
  dPt  = 10

class Number_Variable:
  njet = 0
  nSRjet = 1
  nmuon = 2
  nmuon_p = 3
  nmuon_m = 4
  nele = 5
  nele_p = 6
  nele_m = 7
  nlep = 8
  sumPt_SRjet = 9
  sumPt_lep = 10
  sumPt_ZHl = 11
  sumPt_VH = 12
  swap_flag = 13

def addObservables(config):
  from QFramework import TQObservable,INFO,ERROR,BREAK,WARN


  # try:
  #   from HWWAnalysisCode import lvqqObservable
  # except Exception as error:
  #   ERROR("Couldn't import lvqqObservable.h module!\n"+"Message from python:\n"+str(error))
  #   return False


  INFO("adding lvqqObservable")
  #=== The integers must match the correct modes inside HWWLeptonIDObservable.cxx
  njet = lvqqObservable("njet", Number_Variable.njet)
  if not TQObservable.addObservable(njet): return False
  nSRjet = lvqqObservable("nSRjet", Number_Variable.nSRjet)
  if not TQObservable.addObservable(nSRjet): return False
  nmuon = lvqqObservable("nmuon", Number_Variable.nmuon)
  if not TQObservable.addObservable(nmuon): return False
  nmuon_p = lvqqObservable("nmuon_p", Number_Variable.nmuon_p)
  if not TQObservable.addObservable(nmuon_p): return False
  nmuon_m = lvqqObservable("nmuon_m", Number_Variable.nmuon_m)
  if not TQObservable.addObservable(nmuon_m): return False
  nele = lvqqObservable("nele", Number_Variable.nele)
  if not TQObservable.addObservable(nele): return False
  nele_p = lvqqObservable("nele_p", Number_Variable.nele_p)
  if not TQObservable.addObservable(nele_p): return False
  nele_m = lvqqObservable("nele_m", Number_Variable.nele_m)
  if not TQObservable.addObservable(nele_m): return False
  nlep = lvqqObservable("nlep", Number_Variable.nlep)
  if not TQObservable.addObservable(nlep): return False
  sumPt_SRjet = lvqqObservable("sumPt_SRjet", Number_Variable.sumPt_SRjet)
  if not TQObservable.addObservable(sumPt_SRjet): return False
  sumPt_lep = lvqqObservable("sumPt_lep", Number_Variable.sumPt_lep)
  if not TQObservable.addObservable(sumPt_lep): return False
  sumPt_ZHl = lvqqObservable("sumPt_ZHl", Number_Variable.sumPt_ZHl)
  if not TQObservable.addObservable(sumPt_ZHl): return False
  sumPt_VH = lvqqObservable("sumPt_VH", Number_Variable.sumPt_VH)
  if not TQObservable.addObservable(sumPt_VH): return False
  swap_flag = lvqqObservable("swap_flag", Number_Variable.swap_flag)
  if not TQObservable.addObservable(swap_flag): return False
  ######################################
  MET = lvqqObservable("MET", Interested_Obj1.miss, Interested_Variable.e)
  if not TQObservable.addObservable(MET): return False

  lep1_pt = lvqqObservable("lep1_pt", Interested_Obj1.lep1, Interested_Variable.pt)
  if not TQObservable.addObservable(lep1_pt): return False
  lep1_eta = lvqqObservable("lep1_eta", Interested_Obj1.lep1, Interested_Variable.eta)   
  if not TQObservable.addObservable(lep1_eta): return False
  lep1_e = lvqqObservable("lep1_e", Interested_Obj1.lep1, Interested_Variable.e)
  if not TQObservable.addObservable(lep1_e): return False
    
  lep2_pt = lvqqObservable("lep2_pt", Interested_Obj1.lep2, Interested_Variable.pt)
  if not TQObservable.addObservable(lep2_pt): return False
  lep2_eta = lvqqObservable("lep2_eta", Interested_Obj1.lep2, Interested_Variable.eta)   
  if not TQObservable.addObservable(lep2_eta): return False
  lep2_e = lvqqObservable("lep2_e", Interested_Obj1.lep2, Interested_Variable.e)
  if not TQObservable.addObservable(lep2_e): return False
  
  lep3_pt = lvqqObservable("lep3_pt", Interested_Obj1.lep3, Interested_Variable.pt)
  if not TQObservable.addObservable(lep3_pt): return False
  lep3_eta = lvqqObservable("lep3_eta", Interested_Obj1.lep3, Interested_Variable.eta)   
  if not TQObservable.addObservable(lep3_eta): return False
  lep3_e = lvqqObservable("lep3_e", Interested_Obj1.lep3, Interested_Variable.e)
  if not TQObservable.addObservable(lep3_e): return False

  SRjet1_pt = lvqqObservable("SRjet1_pt", Interested_Obj1.SRjet1, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_pt): return False
  SRjet1_eta = lvqqObservable("SRjet1_eta", Interested_Obj1.SRjet1, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_eta): return False
  SRjet1_e = lvqqObservable("SRjet1_e", Interested_Obj1.SRjet1, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_e): return False
  SRjet1_m = lvqqObservable("SRjet1_m", Interested_Obj1.SRjet1, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_m): return False

  SRjet2_pt = lvqqObservable("SRjet2_pt", Interested_Obj1.SRjet2, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_pt): return False
  SRjet2_eta = lvqqObservable("SRjet2_eta", Interested_Obj1.SRjet2, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_eta): return False
  SRjet2_e = lvqqObservable("SRjet2_e", Interested_Obj1.SRjet2, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_e): return False
  SRjet2_m = lvqqObservable("SRjet2_m", Interested_Obj1.SRjet2, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_m): return False

  SRjet3_pt = lvqqObservable("SRjet3_pt", Interested_Obj1.SRjet3, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet3_pt): return False
  SRjet3_eta = lvqqObservable("SRjet3_eta", Interested_Obj1.SRjet3, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet3_eta): return False
  SRjet3_e = lvqqObservable("SRjet3_e", Interested_Obj1.SRjet3, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet3_e): return False
  SRjet3_m = lvqqObservable("SRjet3_m", Interested_Obj1.SRjet3, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet3_m): return False

  jet1_pt = lvqqObservable("jet1_pt", Interested_Obj1.jet1, Interested_Variable.pt)
  if not TQObservable.addObservable(jet1_pt): return False
  jet1_eta = lvqqObservable("jet1_eta", Interested_Obj1.jet1, Interested_Variable.eta)   
  if not TQObservable.addObservable(jet1_eta): return False
  jet1_e = lvqqObservable("jet1_e", Interested_Obj1.jet1, Interested_Variable.e)
  if not TQObservable.addObservable(jet1_e): return False
  jet1_m = lvqqObservable("jet1_m", Interested_Obj1.jet1, Interested_Variable.m)
  if not TQObservable.addObservable(jet1_m): return False
    
  Hlep_pt = lvqqObservable("Hlep_pt", Interested_Obj1.Hlep, Interested_Variable.pt)
  if not TQObservable.addObservable(Hlep_pt): return False
  Hlep_eta = lvqqObservable("Hlep_eta", Interested_Obj1.Hlep, Interested_Variable.eta)   
  if not TQObservable.addObservable(Hlep_eta): return False
  Hlep_e = lvqqObservable("Hlep_e", Interested_Obj1.Hlep, Interested_Variable.e)
  if not TQObservable.addObservable(Hlep_e): return False
  Hlep_charge = lvqqObservable("Hlep_charge", Interested_Obj1.Hlep, Interested_Variable.charge)
  if not TQObservable.addObservable(Hlep_charge): return False

  Vlep_pt = lvqqObservable("Vlep_pt", Interested_Obj1.Vlep, Interested_Variable.pt)
  if not TQObservable.addObservable(Vlep_pt): return False
  Vlep_eta = lvqqObservable("Vlep_eta", Interested_Obj1.Vlep, Interested_Variable.eta)   
  if not TQObservable.addObservable(Vlep_eta): return False
  Vlep_e = lvqqObservable("Vlep_e", Interested_Obj1.Vlep, Interested_Variable.e)
  if not TQObservable.addObservable(Vlep_e): return False
  Vlep_charge = lvqqObservable("Vlep_charge", Interested_Obj1.Vlep, Interested_Variable.charge)
  if not TQObservable.addObservable(Vlep_charge): return False

  Zlep1_pt = lvqqObservable("Zlep1_pt", Interested_Obj1.Zlep1, Interested_Variable.pt)
  if not TQObservable.addObservable(Zlep1_pt): return False
  Zlep1_eta = lvqqObservable("Zlep1_eta", Interested_Obj1.Zlep1, Interested_Variable.eta)   
  if not TQObservable.addObservable(Zlep1_eta): return False
  Zlep1_e = lvqqObservable("Zlep1_e", Interested_Obj1.Zlep1, Interested_Variable.e)
  if not TQObservable.addObservable(Zlep1_e): return False

  Zlep2_pt = lvqqObservable("Zlep2_pt", Interested_Obj1.Zlep2, Interested_Variable.pt)
  if not TQObservable.addObservable(Zlep2_pt): return False
  Zlep2_eta = lvqqObservable("Zlep2_eta", Interested_Obj1.Zlep2, Interested_Variable.eta)   
  if not TQObservable.addObservable(Zlep2_eta): return False
  Zlep2_e = lvqqObservable("Zlep2_e", Interested_Obj1.Zlep2, Interested_Variable.e)
  if not TQObservable.addObservable(Zlep2_e): return False

  ZBoson_pt = lvqqObservable("ZBoson_pt", Interested_Obj1.ZBoson, Interested_Variable.pt)
  if not TQObservable.addObservable(ZBoson_pt): return False
  ZBoson_eta = lvqqObservable("ZBoson_eta", Interested_Obj1.ZBoson, Interested_Variable.eta)   
  if not TQObservable.addObservable(ZBoson_eta): return False
  ZBoson_e = lvqqObservable("ZBoson_e", Interested_Obj1.ZBoson, Interested_Variable.e)
  if not TQObservable.addObservable(ZBoson_e): return False
  ZBoson_m = lvqqObservable("ZBoson_m", Interested_Obj1.ZBoson, Interested_Variable.m)
  if not TQObservable.addObservable(ZBoson_m): return False
    
  ZBoson_cand_pt = lvqqObservable("ZBoson_cand_pt", Interested_Obj1.ZBoson_cand, Interested_Variable.pt)
  if not TQObservable.addObservable(ZBoson_cand_pt): return False
  ZBoson_cand_eta = lvqqObservable("ZBoson_cand_eta", Interested_Obj1.ZBoson_cand, Interested_Variable.eta)   
  if not TQObservable.addObservable(ZBoson_cand_eta): return False
  ZBoson_cand_e = lvqqObservable("ZBoson_cand_e", Interested_Obj1.ZBoson_cand, Interested_Variable.e)
  if not TQObservable.addObservable(ZBoson_cand_e): return False
  ZBoson_cand_m = lvqqObservable("ZBoson_cand_m", Interested_Obj1.ZBoson_cand, Interested_Variable.m)
  if not TQObservable.addObservable(ZBoson_cand_m): return False


  HWjj_pt = lvqqObservable("HWjj_pt", Interested_Obj1.HWjj, Interested_Variable.pt)
  if not TQObservable.addObservable(HWjj_pt): return False
  HWjj_eta = lvqqObservable("HWjj_eta", Interested_Obj1.HWjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(HWjj_eta): return False
  HWjj_e = lvqqObservable("HWjj_e", Interested_Obj1.HWjj, Interested_Variable.e)
  if not TQObservable.addObservable(HWjj_e): return False
  HWjj_m = lvqqObservable("HWjj_m", Interested_Obj1.HWjj, Interested_Variable.m)
  if not TQObservable.addObservable(HWjj_m): return False

  VWjj_pt = lvqqObservable("VWjj_pt", Interested_Obj1.VWjj, Interested_Variable.pt)
  if not TQObservable.addObservable(VWjj_pt): return False
  VWjj_eta = lvqqObservable("VWjj_eta", Interested_Obj1.VWjj, Interested_Variable.eta)   
  if not TQObservable.addObservable(VWjj_eta): return False
  VWjj_e = lvqqObservable("VWjj_e", Interested_Obj1.VWjj, Interested_Variable.e)
  if not TQObservable.addObservable(VWjj_e): return False
  VWjj_m = lvqqObservable("VWjj_m", Interested_Obj1.VWjj, Interested_Variable.m)
  if not TQObservable.addObservable(VWjj_m): return False

  SRjet1_Vl_pt = lvqqObservable("SRjet1_Vl_pt", Interested_Obj1.SRjet1_Vl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_Vl_pt): return False
  SRjet1_Vl_eta = lvqqObservable("SRjet1_Vl_eta", Interested_Obj1.SRjet1_Vl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_Vl_eta): return False
  SRjet1_Vl_e = lvqqObservable("SRjet1_Vl_e", Interested_Obj1.SRjet1_Vl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_Vl_e): return False
  SRjet1_Vl_m = lvqqObservable("SRjet1_Vl_m", Interested_Obj1.SRjet1_Vl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_Vl_m): return False

  SRjet2_Vl_pt = lvqqObservable("SRjet2_Vl_pt", Interested_Obj1.SRjet2_Vl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_Vl_pt): return False
  SRjet2_Vl_eta = lvqqObservable("SRjet2_Vl_eta", Interested_Obj1.SRjet2_Vl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_Vl_eta): return False
  SRjet2_Vl_e = lvqqObservable("SRjet2_Vl_e", Interested_Obj1.SRjet2_Vl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_Vl_e): return False
  SRjet2_Vl_m = lvqqObservable("SRjet2_Vl_m", Interested_Obj1.SRjet2_Vl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_Vl_m): return False

  SRjet1_Hl_pt = lvqqObservable("SRjet1_Hl_pt", Interested_Obj1.SRjet1_Hl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet1_Hl_pt): return False
  SRjet1_Hl_eta = lvqqObservable("SRjet1_Hl_eta", Interested_Obj1.SRjet1_Hl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet1_Hl_eta): return False
  SRjet1_Hl_e = lvqqObservable("SRjet1_Hl_e", Interested_Obj1.SRjet1_Hl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet1_Hl_e): return False
  SRjet1_Hl_m = lvqqObservable("SRjet1_Hl_m", Interested_Obj1.SRjet1_Hl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet1_Hl_m): return False

  SRjet2_Hl_pt = lvqqObservable("SRjet2_Hl_pt", Interested_Obj1.SRjet2_Hl, Interested_Variable.pt)
  if not TQObservable.addObservable(SRjet2_Hl_pt): return False
  SRjet2_Hl_eta = lvqqObservable("SRjet2_Hl_eta", Interested_Obj1.SRjet2_Hl, Interested_Variable.eta)   
  if not TQObservable.addObservable(SRjet2_Hl_eta): return False
  SRjet2_Hl_e = lvqqObservable("SRjet2_Hl_e", Interested_Obj1.SRjet2_Hl, Interested_Variable.e)
  if not TQObservable.addObservable(SRjet2_Hl_e): return False
  SRjet2_Hl_m = lvqqObservable("SRjet2_Hl_m", Interested_Obj1.SRjet2_Hl, Interested_Variable.m)
  if not TQObservable.addObservable(SRjet2_Hl_m): return False
  

  HBoson_pt = lvqqObservable("HBoson_pt", Interested_Obj1.HBoson, Interested_Variable.pt)
  if not TQObservable.addObservable(HBoson_pt): return False
  HBoson_eta = lvqqObservable("HBoson_eta", Interested_Obj1.HBoson, Interested_Variable.eta)   
  if not TQObservable.addObservable(HBoson_eta): return False
  HBoson_e = lvqqObservable("HBoson_e", Interested_Obj1.HBoson, Interested_Variable.e)
  if not TQObservable.addObservable(HBoson_e): return False
  HBoson_m = lvqqObservable("HBoson_m", Interested_Obj1.HBoson, Interested_Variable.m)
  if not TQObservable.addObservable(HBoson_m): return False

  all_vis_pt = lvqqObservable("all_vis_pt", Interested_Obj1.all_vis, Interested_Variable.pt)
  if not TQObservable.addObservable(all_vis_pt): return False
  all_vis_eta = lvqqObservable("all_vis_eta", Interested_Obj1.all_vis, Interested_Variable.eta)   
  if not TQObservable.addObservable(all_vis_eta): return False
  all_vis_e = lvqqObservable("all_vis_e", Interested_Obj1.all_vis, Interested_Variable.e)
  if not TQObservable.addObservable(all_vis_e): return False
  all_vis_m = lvqqObservable("all_vis_m", Interested_Obj1.all_vis, Interested_Variable.m)
  if not TQObservable.addObservable(all_vis_m): return False

  
  Hlep_mT = lvqqObservable("Hlep_mT", Interested_Obj1.Hlep, Interested_Variable.mT)
  if not TQObservable.addObservable(Hlep_mT): return False
  HBoson_mT = lvqqObservable("HBoson_mT", Interested_Obj1.HBoson, Interested_Variable.mT)
  if not TQObservable.addObservable(HBoson_mT): return False
  
  
  ######################################
  dR_HlVl = lvqqObservable("dR_HlVl", Interested_Obj1.Hlep, Interested_Obj2.Vlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlVl): return False
  dR_HfHl = lvqqObservable("dR_HfHl", Interested_Obj1.jet1, Interested_Obj2.Hlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfHl): return False
  dR_HfVl = lvqqObservable("dR_HfVl", Interested_Obj1.jet1, Interested_Obj2.Vlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfVl): return False

  dR_HjjHl = lvqqObservable("dR_HjjHl", Interested_Obj1.HWjj, Interested_Obj2.Hlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HjjHl): return False
  dR_HjjVl = lvqqObservable("dR_HjjVl", Interested_Obj1.HWjj, Interested_Obj2.Vlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HjjVl): return False
  dR_HjjHf = lvqqObservable("dR_HjjHf", Interested_Obj1.HWjj, Interested_Obj2.jet1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HjjHf): return False

  dR_HbVl = lvqqObservable("dR_HbVl", Interested_Obj1.HBoson, Interested_Obj2.Vlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HbVl): return False
  dR_AvMiss = lvqqObservable("dR_AvMiss", Interested_Obj1.all_vis, Interested_Obj2.miss, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_AvMiss): return False
    
  dR_Zl12 = lvqqObservable("dR_Zl12", Interested_Obj1.Zlep1, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Zl12): return False
  dR_HlZl1 = lvqqObservable("dR_HlZl1", Interested_Obj1.Hlep, Interested_Obj2.Zlep1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlZl1): return False
  dR_HlZl2 = lvqqObservable("dR_HlZl2", Interested_Obj1.Hlep, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlZl2): return False
  dR_HfZl1 = lvqqObservable("dR_HfZl1", Interested_Obj1.jet1, Interested_Obj2.Zlep1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfZl1): return False
  dR_HfZl2 = lvqqObservable("dR_HfZl2", Interested_Obj1.jet1, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfZl2): return False
  dR_HjjZl1 = lvqqObservable("dR_HjjZl1", Interested_Obj1.HWjj, Interested_Obj2.Zlep1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HjjZl1): return False
  dR_HjjZl2 = lvqqObservable("dR_HjjZl2", Interested_Obj1.HWjj, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HjjZl2): return False

  dR_cand_Zl12 = lvqqObservable("dR_cand_Zl12", Interested_Obj1.up_cand, Interested_Obj2.um_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_Zl12): return False
  dR_cand_HlZl1 = lvqqObservable("dR_cand_HlZl1", Interested_Obj1.u3_cand, Interested_Obj2.up_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_HlZl1): return False
  dR_cand_HlZl2 = lvqqObservable("dR_cand_HlZl2", Interested_Obj1.u3_cand, Interested_Obj2.um_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_HlZl2): return False
  dR_cand_HfZl1 = lvqqObservable("dR_cand_HfZl1", Interested_Obj1.jet1, Interested_Obj2.up_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_HfZl1): return False
  dR_cand_HfZl2 = lvqqObservable("dR_cand_HfZl2", Interested_Obj1.jet1, Interested_Obj2.um_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_HfZl2): return False
  dR_cand_HfHl = lvqqObservable("dR_cand_HfHl", Interested_Obj1.jet1, Interested_Obj2.u3_cand, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_cand_HfHl): return False
  
  

  dR_Hl_SRjet1_Hl = lvqqObservable("dR_Hl_SRjet1_Hl", Interested_Obj1.Hlep, Interested_Obj2.SRjet1_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet1_Hl): return False
  dR_Hl_SRjet2_Hl = lvqqObservable("dR_Hl_SRjet2_Hl", Interested_Obj1.Hlep, Interested_Obj2.SRjet2_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet2_Hl): return False
  dR_SRjet12_Hl = lvqqObservable("dR_SRjet12_Hl", Interested_Obj1.SRjet1_Hl, Interested_Obj2.SRjet2_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_Hl): return False

  dR_Vl_SRjet1_Vl = lvqqObservable("dR_Vl_SRjet1_Vl", Interested_Obj1.Vlep, Interested_Obj2.SRjet1_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet1_Vl): return False
  dR_Vl_SRjet2_Vl = lvqqObservable("dR_Vl_SRjet2_Vl", Interested_Obj1.Vlep, Interested_Obj2.SRjet2_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet2_Vl): return False
  dR_SRjet12_Vl = lvqqObservable("dR_SRjet12_Vl", Interested_Obj1.SRjet1_Vl, Interested_Obj2.SRjet2_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_Vl): return False


  dR_Hl_SRjet1_Vl = lvqqObservable("dR_Hl_SRjet1_Vl", Interested_Obj1.Hlep, Interested_Obj2.SRjet1_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet1_Vl): return False
  dR_Hl_SRjet2_Vl = lvqqObservable("dR_Hl_SRjet2_Vl", Interested_Obj1.Hlep, Interested_Obj2.SRjet2_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet2_Vl): return False

  dR_Vl_SRjet1_Hl = lvqqObservable("dR_Vl_SRjet1_Hl", Interested_Obj1.Vlep, Interested_Obj2.SRjet1_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet1_Hl): return False
  dR_Vl_SRjet2_Hl = lvqqObservable("dR_Vl_SRjet2_Hl", Interested_Obj1.Vlep, Interested_Obj2.SRjet2_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet2_Hl): return False



  
  return True

if __name__ == "__main__":
  print "Inside main of lvqqObservable python snippet"
  if not addObservables():
    print("Couldn't add lvqqObservable!")
  else:
    print("Successfully added lvqqObservable")
