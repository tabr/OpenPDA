#ifndef GAMETEMPLATE_EFFECTS_H_
#define GAMETEMPLATE_EFFECTS_H_
  //artefacts->
  PlayerEffect_ModRadDoseClass* ArtefactMedusa              = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE, 5, 0, TemporaryClass::PLAYEREFFECT_ART_MEDUSA, (char*)"medusa");
  ArtefactMedusa->SetDoseValue(-1);
  GameCFG.RegisterNewPlayerEffect(ArtefactMedusa);

  PlayerEffect_CombinedClass*  ArtefactEzh                  = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0, TemporaryClass::PLAYEREFFECT_ART_EZH, (char*)"ezh");

  PlayerEffect_ModRadDoseClass* ArtefactEzh_Dose            = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,3,0, TemporaryClass::PLAYEREFFECT_ART_EZH1, (char*)"ezh1");//each 3 sec +1 dose
  ArtefactEzh_Dose->SetDoseValue(1);
  PlayerEffect_HealClass* ArtefactEzh_Heal                  = new PlayerEffect_HealClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0, TemporaryClass::PLAYEREFFECT_ART_EZH2, (char*)"ezh2");//each 5 sec +1 hp
  ArtefactEzh_Heal->SetHealValue(1);
  PlayerEffects_Interface** ArtefactEzh_array               = new PlayerEffects_Interface*[2]{ArtefactEzh_Dose,ArtefactEzh_Heal};
  ArtefactEzh->SetCombined(ArtefactEzh_array,2);
  GameCFG.RegisterNewPlayerEffect(ArtefactEzh);

  PlayerEffect_HealClass* ArtefactDusha_Heal                = new PlayerEffect_HealClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0, TemporaryClass::PLAYEREFFECT_ART_DUSHA, (char*)"dusha");//each 5 sec +1 hp
  ArtefactDusha_Heal->SetHealValue(1);
  GameCFG.RegisterNewPlayerEffect(ArtefactDusha_Heal);

  PlayerEffect_CombinedClass*  ArtefactKamCvetok            = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0, TemporaryClass::PLAYEREFFECT_ART_KAM_CVET, (char*)"kam cv");
  PlayerEffect_ModHealthClass* ArtefactKamCvetok_Dmg        = new PlayerEffect_ModHealthClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,7,0, TemporaryClass::PLAYEREFFECT_ART_KAM_CVET1, (char*)"kam cv1");//each 7 sec -1 hp
  ArtefactKamCvetok_Dmg->SetModHealthValue(-1);
  PlayerEffect_ModRadDoseClass* ArtefactKamCvetok_Dose      = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0, TemporaryClass::PLAYEREFFECT_ART_KAM_CVET2, (char*)"kam cv2");
  ArtefactKamCvetok_Dose->SetDoseValue(-1);
  PlayerEffects_Interface** ArtefactKamCvetok_array         = new PlayerEffects_Interface*[2]{ArtefactKamCvetok_Dose,ArtefactKamCvetok_Dmg};
  ArtefactKamCvetok->SetCombined(ArtefactKamCvetok_array,2);
  GameCFG.RegisterNewPlayerEffect(ArtefactDusha_Heal);
/*




  PlayerEffect_ModRadDoseClass* ArtefactVspyshka_Dose       = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,1,0);//each 1 sec +1 dose
  ArtefactVspyshka_Dose->SetDoseValue(1);
  PlayerEffect_DefDamageSourceClass* ArtefactVspyshka_Def   = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactVspyshka_Def->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_ELECTRICITY, 10);

  PlayerEffect_ModRadDoseClass* ArtefactOgnShar_Dose        = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,3,0);//each 3 sec +1 dose
  ArtefactOgnShar_Dose->SetDoseValue(1);
  PlayerEffect_DefDamageSourceClass* ArtefactOgnShar_Def    = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactOgnShar_Def->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_FIRE, 10);

  PlayerEffect_ModRadDoseClass* ArtefactPlenka_Dose         = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0);//each 5 sec +1 dose
  ArtefactPlenka_Dose->SetDoseValue(1);
  PlayerEffect_DefDamageSourceClass* ArtefactPlenka_Def     = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactPlenka_Def->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_CHEMICAL, 30);

  PlayerEffect_ModRadDoseClass* ArtefactPustishka_Dose      = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,3,0);//each 3 sec +1 dose
  ArtefactPustishka_Dose->SetDoseValue(1);
  PlayerEffect_DefDamageSourceClass* ArtefactPustishka_Def  = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactPustishka_Def->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_ELECTRICITY, 10);

  PlayerEffect_ModRadDoseClass* ArtefactLunSvet_Dose        = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,3,0);//each 3 sec +2dose
  ArtefactLunSvet_Dose->SetDoseValue(2);
  PlayerEffect_DefDamageSourceClass* ArtefactLunSvet_Def    = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactLunSvet_Def->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_ELECTRICITY, 30);


  PlayerEffect_ModRadDoseClass* ArtefactCrystal_Dose        = new PlayerEffect_ModRadDoseClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0);//each 5 sec +1 dose
  ArtefactCrystal_Dose->SetDoseValue(1);
  PlayerEffect_HealClass* ArtefactCrystal_Heal              = new PlayerEffect_HealClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,5,0);//each 5 sec +1 hp
  ArtefactCrystal_Heal->SetHealValue(1);
  PlayerEffect_DefDamageSourceClass* ArtefactCrystal_Def1   = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactCrystal_Def1->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_FIRE, 30);
  PlayerEffect_DefDamageSourceClass* ArtefactCrystal_Def2   = new PlayerEffect_DefDamageSourceClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  ArtefactCrystal_Def2->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_PSY, 10);



  PlayerEffect_CombinedClass*  ArtefactKamCvetok            = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactKamCvetok_array          = new PlayerEffectsInterface*[2]{ArtefactKamCvetok_Dose,ArtefactKamCvetok_Def};
  ArtefactKamCvetok->SetCombined(ArtefactKamCvetok_array,2);

  PlayerEffect_CombinedClass*  ArtefactVspyshka             = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactVspyshka_array           = new PlayerEffectsInterface*[2]{ArtefactVspyshka_Dose,ArtefactVspyshka_Def};
  ArtefactVspyshka->SetCombined(ArtefactVspyshka_array,2);

  PlayerEffect_CombinedClass*  ArtefactOgnShar              = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactOgnShar_array            = new PlayerEffectsInterface*[2]{ArtefactOgnShar_Dose,ArtefactOgnShar_Def};
  ArtefactOgnShar->SetCombined(ArtefactOgnShar_array,2);

  PlayerEffect_CombinedClass*  ArtefactPlenka               = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactPlenka_array             = new PlayerEffectsInterface*[2]{ArtefactPlenka_Dose,ArtefactPlenka_Def};
  ArtefactPlenka->SetCombined(ArtefactPlenka_array,2);

  PlayerEffect_CombinedClass*  ArtefactPustishka            = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactPustishka_array          = new PlayerEffectsInterface*[2]{ArtefactPustishka_Dose,ArtefactPustishka_Def};
  ArtefactPustishka->SetCombined(ArtefactPustishka_array,2);

  PlayerEffect_CombinedClass*  ArtefactLunSvet              = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactLunSvet_array            = new PlayerEffectsInterface*[2]{ArtefactLunSvet_Dose,ArtefactLunSvet_Def};
  ArtefactLunSvet->SetCombined(ArtefactLunSvet_array,2);

  PlayerEffect_CombinedClass*  ArtefactCrystal              = new PlayerEffect_CombinedClass(1<<PE_CFG::PE_CFG_TICK_INFINILTY_UNTIL_DIE,255,0);
  PlayerEffectsInterface** ArtefactCrystal_array            = new PlayerEffectsInterface*[4]{ArtefactCrystal_Dose,ArtefactCrystal_Heal,ArtefactCrystal_Def1,ArtefactCrystal_Def2};
  ArtefactCrystal->SetCombined(ArtefactCrystal_array,4);


  //<-artefacts

*/
  
  //items ->
  PlayerEffect_DefDamageSourceClass* Item_PsyBlok        = new PlayerEffect_DefDamageSourceClass(0, 60, 10, TemporaryClass::PLAYEREFFECT_ITEM_PLYSBLOCK, (char*)"PsyBlock");//10 min
  Item_PsyBlok->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_PSY, 20);
  GameCFG.RegisterNewPlayerEffect(Item_PsyBlok);

  PlayerEffect_DefDamageSourceClass* Item_Radioprotector = new PlayerEffect_DefDamageSourceClass(0, 60, 20, TemporaryClass::PLAYEREFFECT_ITEM_RADIOPROTECTOR, (char*)"RadProtector");//60sec*20 = 20 min
  Item_Radioprotector->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_RADIATION_EXTERNAL, 60);//80%
  GameCFG.RegisterNewPlayerEffect(Item_Radioprotector);

  PlayerEffect_HealClass* Item_FirstAidKit               = new PlayerEffect_HealClass(0, 1, 50, TemporaryClass::PLAYEREFFECT_ITEM_FIRSTAIDKIT, (char*)"FirstAid");//50 ticks +1hp
  Item_FirstAidKit->SetHealValue(1);
  GameCFG.RegisterNewPlayerEffect(Item_FirstAidKit);

  PlayerEffect_HealClass* Item_Bandage                   = new PlayerEffect_HealClass(0, 1, 10, TemporaryClass::PLAYEREFFECT_ITEM_BANDAGE, (char*)"Bandage");//10 ticks +1hp
  Item_Bandage->SetHealValue(1);
  GameCFG.RegisterNewPlayerEffect(Item_Bandage);

  PlayerEffect_ModRadDoseClass* Item_Antiradin           = new PlayerEffect_ModRadDoseClass(0, 1, 90, TemporaryClass::PLAYEREFFECT_ITEM_ANTIRADIN, (char*)"AntiRadin");//90 ticks -1 dose
  Item_Antiradin->SetDoseValue(-1);
  GameCFG.RegisterNewPlayerEffect(Item_Antiradin);


//  PlayerEffect_SafeShelterClass* EffectSafeShelter  = new PlayerEffect_SafeShelterClass(0, 1, 30, TemporaryClass::PLAYEREFFECT_SAFE_SHELTER, (char*)"SafeShelter");//30 sec
  EffectSafeShelterHack  = new PlayerEffect_SafeShelterClass(0, 1, 30, TemporaryClass::PLAYEREFFECT_SAFE_SHELTER, (char*)"SafeShelter");//30 sec
  GameCFG.RegisterNewPlayerEffect(EffectSafeShelterHack);


  
  
  //PlayerEffect_DeathTimerClass* Item_EnclaveChip30      = new PlayerEffect_DeathTimerClass(0, 60, 30);//60sec*30 = 30 min
  //Item_EnclaveChip30->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_BIO);

  //PlayerEffect_DeathTimerClass* Item_EnclaveChip45      = new PlayerEffect_DeathTimerClass(0, 60, 45);//60sec*45 = 45 min
  //Item_EnclaveChip30->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_BIO);

  //PlayerEffect_DeathTimerClass* Item_EnclaveChip60      = new PlayerEffect_DeathTimerClass(0, 60, 60);//60sec*60 = 60 min
  //Item_EnclaveChip30->SetDmgSrc(DamageSource_t::DAMAGE_SOURCE_BIO);


  //PlayerEffect_FoodClass* EffectFood              = new PlayerEffect_FoodClass(0, 1, 30);//30 sec
  //<-items



#endif /* GAMETEMPLATE_EFFECTS_H_ */