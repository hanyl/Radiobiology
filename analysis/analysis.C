void analysis(){
  TString fileName("Injector_5GeV");

  mergeFile(fileName);

  TFile * fileROOT  = new TFile(fileName + ".root", "READ");
  TTree *tree = (TTree*)fileROOT->Get("tree");

  //Double_t x,y,z,px,py,pz,energy;
  Int_t type;

  //tree->SetBranchAddress("x",&x);
  //tree->SetBranchAddress("y",&y);
  //tree->SetBranchAddress("z",&z);
  //tree->SetBranchAddress("px",&px);
  //tree->SetBranchAddress("py",&py);
  //tree->SetBranchAddress("pz",&pz);
  //tree->SetBranchAddress("e",&energy);
  tree->SetBranchAddress("type",&type);

  createHist(5);

  Int_t nPrimaryElectron = 0;
  Int_t nTempElectron = 0;
  Int_t nTempGamma = 0;
  Int_t nFinalPositron = 0;
  Long64_t nentries = tree->GetEntries();
  for(Long64_t i = 0; i<nentries; i++) {
    tree->GetEntry(i);

    switch(type) {
      case 0:   // Primary electron
        {
          nPrimaryElectron++;
          break;
        }
      case 1:   // Electron after channeling
        {
          nTempElectron++;
          break;
        }
      case 2:   // gamma after channeling
        {
          nTempGamma++;
          break;
        }
      case 3:   // Final positron
        {
          nFinalPositron++;
          break;
        }
    }

  }

  fillHist(tree);
  saveHist(fileName);


  std::ofstream ofile("result_" + fileName + ".dat"); 
  ofile<<"The number of electron before Xtal is: "<<nPrimaryElectron<<std::endl;
  ofile<<"The number of electron after Xtal is: "<<nTempElectron<<std::endl;
  ofile<<"The number of gamma after Xtal is: "<<nTempGamma<<std::endl;
  ofile<<"The number of positron before AMD is: "<<nFinalPositron<<std::endl;
  ofile<<"The channeling gamma yield is: "<< 1.0 * nTempGamma/nPrimaryElectron<<std::endl;
  ofile<<"The positron yield before AMD is: "<< 1.0 * nFinalPositron/nPrimaryElectron<<std::endl;
  ofile.close();

  std::cout<<"The channeling gamma yield is: "<< 1.0 * nTempGamma/nPrimaryElectron<<std::endl;
  std::cout<<"The positron yield before AMD is: "<< 1.0 * nFinalPositron/nPrimaryElectron<<std::endl;


  fileROOT->Close();
  delete fileROOT;
}


void mergeFile(TString &fileName){

  TString mergedFile(fileName + ".root");
  TString cmd;

  // remove merged files
  cmd = "rm -f " + mergedFile;
  system((char*)cmd);

  // merge files
  cmd = "hadd " + mergedFile + " " + fileName + "_*.root";
  system((char*)cmd);

}

void createHist(Double_t energy){

  energy += 1;

  TCanvas *c1 = new TCanvas("c1","",200,10,700,900);
  c1->SetLogy();

  TH1D *hx0 = new TH1D("hx0","x for electron before Xtal",100,-10,10);
  TH1D *hy0 = new TH1D("hy0","y for electron before Xtal",100,-10,10);
  TH1D *hz0 = new TH1D("hz0","z for electron before Xtal",100,-10,10);
  TH1D *hpx0 = new TH1D("hpx0","px for electron before Xtal",100,-2e-4,2e-4);
  TH1D *hpy0 = new TH1D("hpy0","py for electron before Xtal",100,-2e-4,2e-4);
  TH1D *hpz0 = new TH1D("hpz0","pz for electron before Xtal",100,-energy,energy);
  TH1D *henergy0 = new TH1D("henergy0","energy for electron before Xtal",100,0,energy);

  TH1D *hx1 = new TH1D("hx1","x for electron after Xtal",100,-10,10);
  TH1D *hy1 = new TH1D("hy1","y for electron after Xtal",100,-10,10);
  TH1D *hz1 = new TH1D("hz1","z for electron after Xtal",100,-10,10);
  TH1D *hpx1 = new TH1D("hpx1","px for electron after Xtal",100,-2e-4,2e-4);
  TH1D *hpy1 = new TH1D("hpy1","py for electron after Xtal",100,-2e-4,2e-4);
  TH1D *hpz1 = new TH1D("hpz1","for electron after Xtal",100,-energy,energy);
  TH1D *henergy1 = new TH1D("henergy1","energy for electron after Xtal",100,0,energy);

  TH1D *hx2 = new TH1D("hx2","x for gamma after Xtal",100,-10,10);
  TH1D *hy2 = new TH1D("hy2","y for gamma after Xtal",100,-10,10);
  TH1D *hz2 = new TH1D("hz2","z for gamma after Xtal",100,-10,10);
  TH1D *hpx2 = new TH1D("hpx2","px for gamma after Xtal",100,-0.1,0.1);
  TH1D *hpy2 = new TH1D("hpy2","py for gamma after Xtal",100,-0.1,0.1);
  TH1D *hpz2 = new TH1D("hpz2","pz for gamma after Xtal",100,-energy,energy);
  TH1D *henergy2 = new TH1D("henergy2","energy for gamma after Xtal",100,0,energy);

  TH1D *hx3 = new TH1D("hx3","x for positron before AMD",100,-15,15);
  TH1D *hy3 = new TH1D("hy3","y for positron before AMD",100,-15,15);
  TH1D *hz3 = new TH1D("hz3","z for positron before AMD",100,-15,15);
  TH1D *hpx3 = new TH1D("hpx3","px for positron before AMD",100,-0.15,0.15);
  TH1D *hpy3 = new TH1D("hpy3","py for positron before AMD",100,-0.15,0.15);
  TH1D *hpz3 = new TH1D("hpz3","pz for positron before AMD",100,-0.15,0.15);
  TH1D *henery3 = new TH1D("henergy3","energy for positron before AMD",100,0,energy);
}

void fillHist(TTree * tree){

  tree->Draw("x >> hx0","type==0");
  tree->Draw("y >> hy0","type==0");
  tree->Draw("z >> hz0","type==0");
  tree->Draw("px >> hpx0","type==0");
  tree->Draw("py >> hpy0","type==0");
  tree->Draw("pz >> hpz0","type==0");
  tree->Draw("e >> henergy0","type==0");

  tree->Draw("x >> hx1","type==1");
  tree->Draw("y >> hy1","type==1");
  tree->Draw("z >> hz1","type==1");
  tree->Draw("px >> hpx1","type==1");
  tree->Draw("py >> hpy1","type==1");
  tree->Draw("pz >> hpz1","type==1");
  tree->Draw("e >> henergy1","type==1");

  tree->Draw("x >> hx2","type==2");
  tree->Draw("y >> hy2","type==2");
  tree->Draw("z >> hz2","type==2");
  tree->Draw("px >> hpx2","type==2");
  tree->Draw("py >> hpy2","type==2");
  tree->Draw("pz >> hpz2","type==2");
  tree->Draw("e >> henergy2","type==2");

  tree->Draw("x >> hx3","type==3");
  tree->Draw("y >> hy3","type==3");
  tree->Draw("z >> hz3","type==3");
  tree->Draw("px >> hpx3","type==3");
  tree->Draw("py >> hpy3","type==3");
  tree->Draw("pz >> hpz3","type==3");
  tree->Draw("e >> henergy3","type==3");

}

void saveAsEps(TString &fileName, TString histName){
  TPostScript ps((char*)fileName,113);
  TH1D * hist = gDirectory->FindObject((char*)histName);
  hist->Draw();
  ps.Close();
}

void saveHist(TString &fileROOT){

  TString tmp;
  for(Int_t i = 0;i <= 3;i++){
    saveAsEps("hist_" + fileROOT + "_hx" + Form("%d",i) + ".eps", tmp + "hx" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_hy" + Form("%d",i) + ".eps", tmp + "hy" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_hz" + Form("%d",i) + ".eps", tmp + "hz" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_hpx" + Form("%d",i) + ".eps", tmp + "hpx" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_hpy" + Form("%d",i) + ".eps", tmp + "hpy" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_hpz" + Form("%d",i) + ".eps", tmp + "hpz" + Form("%d",i));
    saveAsEps("hist_" + fileROOT + "_henergy" + Form("%d",i) + ".eps", tmp + "henergy" + Form("%d",i));
  }
}
