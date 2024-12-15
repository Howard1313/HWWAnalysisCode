from QFramework import TQTreeObservable, INFO, ERROR
import ROOT
from HWWAnalysisCode import CompositeObservable

class Interested_Obj1:
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

class Interested_Obj2:
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
  dR  = 0
  dPhi  = 1
  dEta  = 2
  

def addObservables(config):
  from QFramework import TQObservable,INFO,ERROR,BREAK,WARN

  
  # try:
  #   from HWWAnalysisCode import CompositeObservable
  # except Exception as error:
  #   ERROR("Couldn't import CompositeObservable.h module!\n"+"Message from python:\n"+str(error))
  #   return False


  INFO("adding CompositeObservable")
  #=== The integers must match the correct modes inside HWWLeptonIDObservable.cxx
  dR_HlVl = CompositeObservable("dR_HlVl", Interested_Obj1.Hlep, Interested_Obj2.VWlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlVl): return False
  dR_HfHl = CompositeObservable("dR_HfHl", Interested_Obj1.Hfatjet, Interested_Obj2.Hlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfHl): return False
  dR_HfVl = CompositeObservable("dR_HfVl", Interested_Obj1.Hfatjet, Interested_Obj2.VWlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfVl): return False

  dR_HbVl = CompositeObservable("dR_HbVl", Interested_Obj1.HBoson, Interested_Obj2.VWlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HbVl): return False

  dR_Hl_SRjet1_l2 = CompositeObservable("dR_Hl_SRjet1_l2", Interested_Obj1.Hlep, Interested_Obj2.SRjet1_l2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet1_l2): return False
  dR_Hl_SRjet2_l2 = CompositeObservable("dR_Hl_SRjet2_l2", Interested_Obj1.Hlep, Interested_Obj2.SRjet2_l2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet2_l2): return False
  dR_SRjet12_l2 = CompositeObservable("dR_SRjet12_l2", Interested_Obj1.SRjet1_l2, Interested_Obj2.SRjet2_l2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_l2): return False
    
  dR_Vl_SRjet1_l1 = CompositeObservable("dR_Vl_SRjet1_l1", Interested_Obj1.VWlep, Interested_Obj2.SRjet1_l1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet1_l1): return False
  dR_Vl_SRjet2_l1 = CompositeObservable("dR_Vl_SRjet2_l1", Interested_Obj1.VWlep, Interested_Obj2.SRjet2_l1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet2_l1): return False
  dR_SRjet12_l1 = CompositeObservable("dR_SRjet12_l1", Interested_Obj1.SRjet1_l1, Interested_Obj2.SRjet2_l1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_l1): return False

  dR_Hl_SRjet1_Hl = CompositeObservable("dR_Hl_SRjet1_Hl", Interested_Obj1.Hlep, Interested_Obj2.SRjet1_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet1_Hl): return False
  dR_Hl_SRjet2_Hl = CompositeObservable("dR_Hl_SRjet2_Hl", Interested_Obj1.Hlep, Interested_Obj2.SRjet2_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hl_SRjet2_Hl): return False
  dR_SRjet12_Hl = CompositeObservable("dR_SRjet12_Hl", Interested_Obj1.SRjet1_Hl, Interested_Obj2.SRjet2_Hl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_Hl): return False

  dR_Vl_SRjet1_Vl = CompositeObservable("dR_Vl_SRjet1_Vl", Interested_Obj1.VWlep, Interested_Obj2.SRjet1_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet1_Vl): return False
  dR_Vl_SRjet2_Vl = CompositeObservable("dR_Vl_SRjet2_Vl", Interested_Obj1.VWlep, Interested_Obj2.SRjet2_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Vl_SRjet2_Vl): return False
  dR_SRjet12_Vl = CompositeObservable("dR_SRjet12_Vl", Interested_Obj1.SRjet1_Vl, Interested_Obj2.SRjet2_Vl, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_SRjet12_Vl): return False

  dR_Zl12 = CompositeObservable("dR_Zl12", Interested_Obj1.Zlep1, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Zl12): return False
  dR_HlZl1 = CompositeObservable("dR_HlZl1", Interested_Obj1.Hlep, Interested_Obj2.Zlep1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlZl1): return False
  dR_HlZl2 = CompositeObservable("dR_HlZl2", Interested_Obj1.Hlep, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HlZl2): return False
  dR_HfZl1 = CompositeObservable("dR_HfZl1", Interested_Obj1.Hfatjet, Interested_Obj2.Zlep1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfZl1): return False
  dR_HfZl2 = CompositeObservable("dR_HfZl2", Interested_Obj1.Hfatjet, Interested_Obj2.Zlep2, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_HfZl2): return False

  dR_ZbHl = CompositeObservable("dR_ZbHl", Interested_Obj1.ZBoson, Interested_Obj2.Hlep, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_ZbHl): return False
  dR_ZbHf = CompositeObservable("dR_ZbHf", Interested_Obj1.ZBoson, Interested_Obj2.Hfatjet, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_ZbHf): return False
  dR_ZbHb = CompositeObservable("dR_ZbHb", Interested_Obj1.ZBoson, Interested_Obj2.HBoson, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_ZbHb): return False

  dR_AvMiss = CompositeObservable("dR_AvMiss", Interested_Obj1.all_vis, Interested_Obj2.miss, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_AvMiss): return False

  dR_j1l2Wjj = CompositeObservable("dR_j1l2Wjj", Interested_Obj1.jet1, Interested_Obj2.l2Wjj, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_j1l2Wjj): return False
  dR_Hfl2Wjj = CompositeObservable("dR_Hfl2Wjj", Interested_Obj1.Hfatjet, Interested_Obj2.l2Wjj, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hfl2Wjj): return False
  dR_Hfj1 = CompositeObservable("dR_Hfj1", Interested_Obj1.Hfatjet, Interested_Obj2.jet1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hfj1): return False

  dR_Hll2Wjj = CompositeObservable("dR_Hll2Wjj", Interested_Obj1.Hlep, Interested_Obj2.l2Wjj, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hll2Wjj): return False
  dR_Hlj1 = CompositeObservable("dR_Hlj1", Interested_Obj1.Hlep, Interested_Obj2.jet1, Interested_Variable.dR)
  if not TQObservable.addObservable(dR_Hlj1): return False
    
  return True

if __name__ == "__main__":
  print "Inside main of CompositeObservable python snippet"
  if not addObservables():
    print("Couldn't add CompositeObservable!")
  else:
    print("Successfully added CompositeObservable")


