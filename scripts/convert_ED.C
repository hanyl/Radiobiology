void convert_ED(){

  std::ifstream ifile("ED_Water_octave.dat",ios_base::in);


  TFile * fileROOT  = new TFile("ED_Water.root", "recreate");
  TTree *tree = new TTree("tree","A tree save the deposited energy");

  Double_t x,y,z,de,dede;
  Int_t entry;

  tree->Branch("x",&x,"x/D");
  //tree->Branch("y",&y,"y/D");
  tree->Branch("z",&z,"z/D");
  tree->Branch("de",&de,"de/D");

  Int_t nline = 0;
  TGraph2D *dt = new TGraph2D();

  std::string line;

  while(getline(ifile,line)){
    if (!line.length() || line[0] == '#')
      continue;
    std::istringstream iss(line);
    //iss>>x>>y>>z>>de>>dede>>entry;
    iss>>x>>z>>de;
    tree->Fill();
 
    nline++;
    dt->SetPoint(nline,z,x,de);
  }

  TPostScript ps("edep.eps",113);
  dt->Draw("colz");
  ps.Close();

  system("epstopdf edep.eps");

  tree->Write();
  fileROOT->Close();

  delete fileROOT;
}
