void convert(){
  TString fileName("Injector_5GeV");

  TFile * fileROOT  = new TFile(fileName + ".root", "READ");
  TTree *tree = (TTree*)fileROOT->Get("tree");

  Double_t x,y,z,px,py,pz,energy;
  Int_t type;

  tree->SetBranchAddress("x",&x);
  tree->SetBranchAddress("y",&y);
  tree->SetBranchAddress("z",&z);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("e",&energy);
  tree->SetBranchAddress("type",&type);

  std::ofstream ofile("dist_" + fileName + ".dat"); 
  ofile<<"# x(mm)   y(mm)   px(GeV)   py(GeV)  pz(GeV)  energy(GeV)"<<std::endl;

  Long64_t nentries = tree->GetEntries();
  for(Long64_t i = 0; i<nentries; i++) {
    tree->GetEntry(i);
    if(type == 3){
      ofile<< x<<"\t"<<y<<"\t"<<px<<"\t"<<py<<"\t"<<pz<<"\t"<<energy<<std::endl;
    }
  }

  ofile.close();

  fileROOT->Close();
  delete fileROOT;
}
