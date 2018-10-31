void convert_RF(){
  TString fileName("Injector_5GeV_1");

  TFile * fileROOT  = new TFile(fileName + ".root", "READ");
  TTree *tree = (TTree*)fileROOT->Get("tree");

  Double_t x,y,z,px,py,pz,energy;
  Double_t xp,yp,p_c;
  Int_t type;
  Double_t time;
  Double_t bunch_length = 500e-6;  // meter

  tree->SetBranchAddress("x",&x);   // millimeter
  tree->SetBranchAddress("y",&y);
  tree->SetBranchAddress("z",&z);
  tree->SetBranchAddress("px",&px);  // GeV/c
  tree->SetBranchAddress("py",&py);  // GeV/c
  tree->SetBranchAddress("pz",&pz);  //GeV/c
  tree->SetBranchAddress("e",&energy);
  tree->SetBranchAddress("type",&type);

  std::ofstream ofile("dist_" + fileName + ".dat"); 
  ofile<<"# x(mm) xp(mrad)  y(mm)  yp(mrad) t(mm/c) p_c(MeV/c)"<<std::endl;

  Long64_t nentries = tree->GetEntries();
  for(Long64_t i = 0; i<nentries; i++) {
    tree->GetEntry(i);
    if(type == 3){

      xp = px/pz * 1e3;
      yp = py/pz * 1e3;
      p_c = sqrt(px*px+py*py+pz*pz) * 1e3;
      time = gRandom->Gaus(0,bunch_length) * 1e3 * 299792458.;

      ofile<< x<<"\t"<<xp<<"\t"<<y<<"\t"<<yp<<"\t"<<time<<"\t"<<p_c<<std::endl;
    }
  }

  ofile.close();

  fileROOT->Close();
  delete fileROOT;
}
