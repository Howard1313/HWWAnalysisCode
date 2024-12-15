# -*- mode: tqfolder -*-
# this files name is 'cuts.txt'
# to get proper syntax highlighting and indentation when using emacs,
# add the following line to your .emacs file:
#   (load-file "$TQPATH/share/tqfolder.el")

+CutChannels {
  # to use the per-event event weights properly, use "Weight" as .weightExpression here
  <.cutExpression = "[$(fitsChannel)] && $(leptonChargeSelection)", .weightExpression = "$(eventWeight)", .title="Channel Selection">
  +CutTruthMatchSignal {
    <.cutExpression = "[$(doTruthMatch) ? $(FatJetTruthWBosonMatchesCount) >= 1 : 1]",  .title="Truth match signal">
    +CutSTXS {
      <.cutExpression = "$(matchesSTXSbin)", .title = "Signal split into STXS bins">
      +CutJetCleaning {
        <.cutExpression = "$(JetCleaning)", .title="Jet Cleaning">
        +CutTrigger {
          <.cutExpression = "[TriggerSelectionDimuObs]", .title="Trigger Selection">  
          +CutBJetVeto{
            <.cutExpression = "$(bJet_n)  == 0", .weightExpression="bTagWeightOTF20", .title="no b-jets">
          }
        }
      }
    }
  }
}
 
@*/CutBJetVeto{
  +Cut_1lep_1u {
    <.cutExpression = "[nmuon] == 1 && [nele] == 0", .title="1muon", nLep_name="1u",nlep="1lep">
  }
  +Cut_2lep_2u0e {
    <.cutExpression = "[nmuon] == 2 && [nele] == 0 && [njet] >= 1", .title="2muon 0ele", nLep_name="2u0e",nlep="2lep">
  }
  +Cut_2lep_1u1e {
    <.cutExpression = "[nmuon] == 1 && [nele] == 1  && [njet] >= 1", .title="1muon 1ele", nLep_name="1u1e",nlep="2lep">
  }
  +Cut_3lep_2u1e {
    <.cutExpression = "[nmuon_p] == 1 && [nmuon_m] == 1 && [nele] == 1", .title="2muon 1ele", nLep_name="2u1e",nlep="3lep">
  }
  +Cut_3lep_3u {
    <.cutExpression = "[nmuon] == 3 && [nmuon_p] >= 1 && [nmuon_m] >= 1 && [njet] >= 1", .title="3muon", nLep_name="3u",nlep="3lep">
  }
  +Cut_3lep_1u2e {
    <.cutExpression = "[nmuon] == 1 && [nele_p] == 1 && [nele_m] == 1 && [njet] >= 1", .title="1muon 2ele", nLep_name="1u2e",nlep="3lep">
  }
}
@*/Cut_1lep_1u*{
  +Cut_$(nLep_name)_Muon1ID {
    <.cutExpression = "[Muon1ID] > 0", .title="Muon1ID">
  }
}

@*/Cut_2lep_2u0e{
  +Cut_$(nLep_name)_Lep1ID {
    <.cutExpression = "[Lep1ID] > 0", .title="Lep1ID">
    +Cut_$(nLep_name)_Lep2ID {
      <.cutExpression = "[Lep2ID] > 0", .title="Lep2ID", nSRjet="all">
      +Cut_$(nLep_name)_Same_Charge {
        <.cutExpression = "[Hlep_charge] == [Vlep_charge]", .title="Same Charge">
        +Cut_$(nLep_name)_lep2_pt_ML{
          <.cutExpression = "[lep2_pt]>20", .title="lep2_pt>20GeV", nSRjet="AfterCut">
        }
      }
    }
  }
}

@*/Cut_2lep_1u1e{
  +Cut_$(nLep_name)_Lep1ID {
    <.cutExpression = "[Lep1ID] > 0", .title="Lep1ID">
    +Cut_$(nLep_name)_Lep2ID_ML {
      <.cutExpression = "[Lep2ID] > 0", .title="Lep2ID", nSRjet="all">
      +Cut_$(nLep_name)_Same_Charge_ML {
        <.cutExpression = "[Hlep_charge] == [Vlep_charge]", .title="Same Charge", nSRjet="SC">
        +Cut_$(nLep_name)_lep2_pt_ML{
          <.cutExpression = "[lep2_pt]>20", .title="lep2_pt>20GeV", nSRjet="AfterCut">
        }
      }
    }
  }
}

@*/Cut_3lep_2u1e*{
  +Cut_$(nLep_name)_Muon1ID {
    <.cutExpression = "[Muon1ID] > 0", .title="Muon1ID">
    +Cut_$(nLep_name)_Muon2ID {
      <.cutExpression = "[Muon2ID] > 0", .title="Muon2ID">
      +Cut_$(nLep_name)_Ele1ID {
        <.cutExpression = "[Ele1ID] > 0", .title="Ele1ID", nSRjet="all">
      }
    }
  }
}

@*/Cut_2u1e_Ele1ID{
  +Cut_$(nLep_name)_Hlep_pt{
    <.cutExpression = "[Hlep_pt]>20", .title="ele_pt>20GeV">
    +Cut_$(nLep_name)_ZBoson_m_ML{
      <.cutExpression = "abs([ZBoson_m]-91.2)<15", .title="|M_upum-Zmass|<15GeV", nSRjet="AfterCut">
    }
  }
}
  
@*/Cut_3lep_3u*{
  +Cut_$(nLep_name)_Muon1ID {
    <.cutExpression = "[Muon1ID] > 0", .title="Muon1ID">
    +Cut_$(nLep_name)_Muon2ID {
      <.cutExpression = "[Muon2ID] > 0", .title="Muon2ID">
      +Cut_$(nLep_name)_Muon3ID {
        <.cutExpression = "[Muon3ID] > 0", .title="Muon3ID", nSRjet="all"> 
      }
    }
  }
}
@*/Cut_3u_Muon3ID{
  +Cut_$(nLep_name)_Hlep_pt{
    <.cutExpression = "[Hlep_pt]>20", .title="u3_pt>20GeV">
    +Cut_$(nLep_name)_ZBoson_m_ML{
      <.cutExpression = "abs([ZBoson_m]-91.2)<15", .title="|M_upum-Zmass|<15GeV", nSRjet="AfterCut">
    }
  }
}

  
@*/Cut_3lep_1u2e*{
  +Cut_$(nLep_name)_Muon1ID {
    <.cutExpression = "[Muon1ID] > 0", .title="Muon1ID">
    +Cut_$(nLep_name)_Ele1ID {
      <.cutExpression = "[Ele1ID] > 0", .title="Ele1ID">
      +Cut_$(nLep_name)_Ele2ID {
        <.cutExpression = "[Ele2ID] > 0", .title="Ele2ID", nSRjet="all">
      }
    }
  }
}
@*/Cut_1u2e_Ele2ID{
  +Cut_$(nLep_name)_epem_pt{
    <.cutExpression = "[Zlep1_pt]>100 && [Zlep2_pt]>20", .title="Zlep1_pt>100GeV,Zlep2_pt>20GeV">
    +Cut_$(nLep_name)_ZBoson_pt{
      <.cutExpression = "[ZBoson_pt]>180", .title="Z_pt>180GeV">
      +Cut_$(nLep_name)_ZBoson_m_ML{
        <.cutExpression = "abs([ZBoson_m]-91.2)<15", .title="|M_epem-Zmass|<15GeV", nSRjet="AfterCut">
      }
    }
  }
}

@*/Cut_*1u1e*_ML{
  +Cut_$(nLep_name)_$(nSRjet)_BDTG{
    <.cutExpression = "$(BDTG_1u1e)>0", .title="BDTG_1u1e>0">
  }
  +Cut_$(nLep_name)_$(nSRjet)_DNN{
    <.cutExpression = "$(DNN_CPU_1u1e)>0.5", .title="DNN_1u1e>0.5">
  }
}

@*/Cut_*2u0e*_ML{
  +Cut_$(nLep_name)_$(nSRjet)_BDTG{
    <.cutExpression = "$(BDTG_2u0e)>0", .title="BDTG_2u0e>0">
  }
  +Cut_$(nLep_name)_$(nSRjet)_DNN{
    <.cutExpression = "$(DNN_CPU_2u0e)>0.5", .title="DNN_2u0e>0.5">
  }
}

@*/Cut_*3u*_ML{
  +Cut_$(nLep_name)_$(nSRjet)_BDTG{
    <.cutExpression = "$(BDTG_3u)>0", .title="BDTG_3u>0">
  }
  +Cut_$(nLep_name)_$(nSRjet)_DNN{
    <.cutExpression = "$(DNN_CPU_3u)>0.5", .title="DNN_3u>0.5">
  }
}

@*/Cut_*2u1e*_ML{
  +Cut_$(nLep_name)_$(nSRjet)_BDTG{
    <.cutExpression = "$(BDTG_2u1e)>0", .title="BDTG_2u1e>0">
  }
  +Cut_$(nLep_name)_$(nSRjet)_DNN{
    <.cutExpression = "$(DNN_CPU_2u1e)>0.5", .title="DNN_2u1e>0.5">
  }
}

@*/Cut_*1u2e*_ML{
  +Cut_$(nLep_name)_$(nSRjet)_BDTG{
    <.cutExpression = "$(BDTG_1u2e)>0", .title="BDTG_1u2e>0">
  }
  +Cut_$(nLep_name)_$(nSRjet)_DNN{
    <.cutExpression = "$(DNN_CPU_1u2e)>0.5", .title="DNN_1u2e>0.5">
  }
}
