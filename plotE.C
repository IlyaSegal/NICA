#include "PlotFunc.C"

void plotE() //Результаты фитирования множественности с ратио и классами центральности для Глаубера
{
  // gROOT->SetStyle("Pub");
  gROOT->ForceStyle();
  // gStyle->SetErrorX(0);

  const int MStyleData[3] = {25, 28, 27};
  const int MStyleFit[3] = {20, 20, 20};
  const int MStyleGl[3] = {22, 22, 22};

  const double MSizeData[3] = {1.4, 1.7, 2.2};
  const double MSizeFit[3] = {1.4, 1.4, 1.4};
  const double MSizeGl[3] = {1.4, 1.4, 1.4};

  Color_t MColor[3] = {1, kBlue + 1, kRed + 2};

  const char *model0 = "urqmd";
  const char *modelT = "UrQMD+GEANT4";
  const char *energ = "9.2";
  const char *sys = "BiBi";
  const char *systemT = Form("Bi+Bi, #sqrt{s_{NN}}=%s GeV", energ);
  const char *energ0 = "9p2";
  const char *outDir = "/home/isegal/NA61/centrality/psd_mult/";

  TPaveText *ptB = new TPaveText(0.45, 0.7, 0.65, 0.92, "NDC NB");
  ptB->AddText(systemT);
  ptB->AddText(modelT);
  //ptB->AddText("N_{hits} > 16, |DCA| < 1 cm");
//  ptB->AddText("N_{hits} > 16, w/o DCA cut");
  //ptB->AddText("Primary only");
  ptB->SetBorderSize(0);
  ptB->SetFillColor(0);
  ptB->SetTextSize(0.035);

  // glaub->Rebin(2);Ideal->Rebin(2);glaub->Rebin(2);
  
  TFile *fileIn = new TFile("/home/isegal/NA61/data/PbPb_pbeam_13AGeV/dcmqgsmsmm/dcmqgsmsmm.qa.root"); // file with modal data mult vs b
  TFile *fileFitGl = new TFile(Form("%s%s",outDir,"glauber_qa.root"));
  TFile *fileFINAL = new TFile(Form("%s%s",outDir,"FINAL.root"));
  

  TH1F *HistData = (TH1F *)fileFitGl->Get("h_psdE");
  TH1F *hfit_histo = (TH1F *)fileFitGl->Get("glaub_fit_histo");
//  TH1F *hfit_histo = new TH1F("new","new",hfit_histo0->GetNbinsX(),0,7750/1.075);
//  for (int i = 0; i < hfit_histo0->GetNbinsX(); i++) hfit_histo->SetBinContent(i, hfit_histo0->GetBinContent(i));
//  hfit_histo->Scale(HistData->Integral()/hfit_histo->Integral());
  TH1F *hDataCP = (TH1F *)HistData->Clone();

//  int Nn = 1.02 * hfit_histo->FindLastBinAbove();
  int Nn = 1.02 * 3000;
  TH2F *hBvsRefMultFit = (TH2F *)fileFitGl->Get("B_VS_Energy+Multiplicity_Histo");
  TH2F *hBvsRefMult = (TH2F *)fileIn->Get("h2_b_psdE");

  TH1F *Data0_10 = (TH1F *)hfit_histo->Clone();
  TH1F *Data10_40 = (TH1F *)hfit_histo->Clone();
  TH1F *Data40_80 = (TH1F *)hfit_histo->Clone();
  Data0_10->Scale(2);
  Data10_40->Scale(2);
  Data40_80->Scale(2);

  hDataCP->Rebin(2);
  hfit_histo->Rebin(2);

  TGraphErrors *GrDataMult, *GrFitMult;
  GrDataMult = HistGraph(hDataCP);
  GrFitMult = HistGraph(hfit_histo);

  TTree *Result = (TTree *)fileFINAL->Get("Result");
  if (!Result)
    return;
  Int_t MinBorder;
  Int_t MaxBorder;
  Int_t fMinBorder;
  Int_t fMaxBorder;
  Float_t MinPercent;
  Float_t MaxPercent;
  Result->SetBranchAddress("MinBorder", &MinBorder);
  Result->SetBranchAddress("MaxBorder", &MaxBorder);
  Result->SetBranchAddress("MinPercent", &MinPercent);
  Result->SetBranchAddress("MaxPercent", &MaxPercent);

  TTree *FitResult = (TTree *)fileFitGl->Get("BestResult");
  if (!FitResult)
    return;

  Float_t mu, f, k, chi2;
  Int_t minNch;
  FitResult->SetBranchAddress("mu", &mu);
  FitResult->SetBranchAddress("f", &f);
  FitResult->SetBranchAddress("k", &k);
  FitResult->SetBranchAddress("chi2", &chi2);
  FitResult->GetEntry(0);

  Int_t const Nclasses = Result->GetEntries();
  Int_t binNch[Nclasses];
  Int_t binNchMax[Nclasses];
  Float_t GlaubV[Nclasses];

  TH1D *HFit[Nclasses];
  TH1D *HData[Nclasses];
  // Color_t color[11] = {kRed + 2, kBlue + 1, 14, kGreen + 3, kMagenta + 3, kGreen + 1, kYellow + 2, 46, kBlue - 9, kViolet + 8, kRed};
  Color_t color[10] = {kRed + 2, kBlue + 1, 14, kGreen + 3, kMagenta + 3, kGreen + 1, kYellow + 2, 46, kBlue - 9, kViolet + 8};

  int IntMinC, IntMaxC;
  double BmeanF[Nclasses], BsigmaF[Nclasses], BmeanErF[Nclasses], BsigmaErF[Nclasses];
  double BmeanD[Nclasses], BsigmaD[Nclasses], BmeanErD[Nclasses], BsigmaErD[Nclasses], centbin[Nclasses], centEr[Nclasses];
  //int range_cent[15] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 90, 100};
  for (int cent = 0; cent < Nclasses; cent++)
  {
    Result->GetEntry(cent);
    IntMaxC = (float)MaxPercent;
    IntMinC = (float)MinPercent;
    fMinBorder = MinBorder;
    fMaxBorder = MaxBorder;

    binNch[cent] = MinBorder;
    binNchMax[cent] = MaxBorder;
    GlaubV[cent] = GrFitMult->Eval(binNchMax[cent]);

//    if (cent == Nclasses - 1)
//    {
//      Result->GetEntry(Nclasses - 2);
//      fMaxBorder = MinBorder;
//      fMinBorder = 1;
//    }

    HFit[cent] = hBvsRefMultFit->ProjectionY(Form("%d_hist_Impact", cent), HistData->FindBin(fMinBorder), HistData->FindBin(fMaxBorder));
    //HFit[cent] = (TH1D *)fileFINAL->Get(Form("B_VS_CentralityClass %d.0%s-%d.0%s", cent * 10, "%", (cent + 1) * 10, "%"));
    // HFit[cent] = (TH1D *)fileFINAL->Get(Form("B_VS_CentralityClass %d%s-%d%s", range_cent[cent], "%", range_cent[(cent + 1)], "%"));
    // cout<<endl<<Form("B_VS_CentralityClass %d%s-%d%s", range_cent[cent], "%", range_cent[(cent + 1)], "%")<<endl;
    HFit[cent]->Scale(1 / HFit[cent]->Integral(1, HFit[cent]->GetNbinsX(), "width"));
    HFit[cent]->SetLineColorAlpha(color[cent], 1);
    BmeanF[cent] = HFit[cent]->GetMean()-1;
    BsigmaF[cent] = HFit[cent]->GetStdDev()/2;
    BmeanErF[cent] = HFit[cent]->GetMeanError();
    BsigmaErF[cent] = HFit[cent]->GetStdDevError();

    HData[cent] = hBvsRefMult->ProjectionX(Form("%d_hist_Impact", cent), HistData->FindBin(fMinBorder), HistData->FindBin(fMaxBorder));
     //HData[cent] = hBvsRefMult->ProjectionY(Form("%d_hist_Impact", cent),fMinBorder, fMaxBorder);
    HData[cent]->Scale(1 / HData[cent]->Integral(1, HData[cent]->GetNbinsX(), "width"));
    HData[cent]->SetLineColorAlpha(color[cent], 1);
    BmeanD[cent] = HData[cent]->GetMean();
    BsigmaD[cent] = HData[cent]->GetStdDev();
    BmeanErD[cent] = HData[cent]->GetMeanError();
    BsigmaErD[cent] = HData[cent]->GetStdDevError();
    centbin[cent] = 0.5 * (IntMinC + IntMaxC);
    centEr[cent] = 0;
  }

  TGraphErrors *GrData = new TGraphErrors(Nclasses, centbin, BmeanD, centEr, BsigmaD);
  GrData->SetMarkerStyle(25);
  GrData->SetMarkerSize(1.5);
  // GrData->SetMarkerColor(4);
  // GrData->SetLineColor(4);
  GrData->GetXaxis()->SetTitle("Centrality, %");
  GrData->GetYaxis()->SetTitle("<b>, fm");
  GrData->SetTitle("");
  GrData->GetYaxis()->SetTitleOffset(1.55);
  GrData->GetYaxis()->SetRangeUser(-0.4, 18);
  GrData->GetXaxis()->SetLimits(0, 100);
  GrData->GetXaxis()->SetNdivisions(210);
  GrData->GetYaxis()->SetTitleSize(0.05);
  GrData->GetYaxis()->SetLabelSize(0.05);
  GrData->GetYaxis()->SetTitleOffset(1.3);
  GrData->GetYaxis()->SetLabelOffset(0.018);
  GrData->SetLineWidth(2.);

  TGraphErrors *GrFit = new TGraphErrors(Nclasses, centbin, BmeanF, centEr, BsigmaF);
  GrFit->SetMarkerStyle(MStyleGl[0]);
  GrFit->SetMarkerSize(1.4);
  GrFit->SetMarkerColorAlpha(MColor[1], 1);
  GrFit->SetLineColorAlpha(MColor[1], 1);
  GrFit->SetLineWidth(2.);
  GrFit->SetTitle("");
  GrFit->GetXaxis()->SetTitle("Centrality, %");
  GrFit->GetYaxis()->SetTitle("<b>, fm");
  TGraphErrors *GrRatio = RatioGr(GrFit, GrData, 0, 0.85, 100, 1.15);
  GrRatio->SetTitle("");
  GrRatio->GetYaxis()->SetTitle("MC-Gl/Model");
  GrRatio->GetXaxis()->SetTitle("Centrality, %");
  GrRatio->GetXaxis()->SetTitleSize(0.1);
  GrRatio->GetXaxis()->SetLabelSize(0.1);
  GrRatio->GetYaxis()->SetTitleSize(0.1);
  GrRatio->GetYaxis()->SetLabelSize(0.1);
  GrRatio->GetYaxis()->SetTitleOffset(0.65);
  GrRatio->GetXaxis()->SetTitleOffset(1.5);
  GrRatio->GetYaxis()->SetLabelOffset(0.013);
  GrRatio->GetXaxis()->SetLabelOffset(0.04);
  GrRatio->GetXaxis()->SetNdivisions(210);
  GrRatio->GetYaxis()->SetNdivisions(505);
  GrRatio->GetXaxis()->SetTickLength(0.1);
  GrRatio->GetYaxis()->CenterTitle(true);
  TCanvas *CRatio2 = new TCanvas("CRatio_of_BMean2", "CRatio2", 800, 800);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.13);
  pad1->SetBottomMargin(0);
  pad1->SetTopMargin(0.05);
  pad1->SetRightMargin(0.03);
  pad1->Draw();
  pad1->cd();
  GrData->Draw("AP");
  GrFit->Draw("SAME P");
  GrData->Draw("SAME P");
  // TLegend *legdif = new TLegend(0.2, 0.7, 0.4, 0.9);
  TLegend *legdif = new TLegend(0.65, 0.15, 0.85, 0.3);
  legdif->SetBorderSize(0);
  legdif->AddEntry(GrData, "Model", "p");
  legdif->AddEntry(GrFit, "MC-Gl", "p");
  legdif->SetTextSize(0.035);
  legdif->Draw();
  ptB->Draw();

  CRatio2->cd(); // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
  pad2->SetLeftMargin(0.13);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(0.0);
  pad2->SetRightMargin(0.03);
  pad2->Draw();
  pad2->cd();

  GrRatio->Draw("AP");
  TLine lineB;
  lineB.SetLineWidth(2);
  lineB.SetLineStyle(2);
  lineB.DrawLine(0, 1, 100, 1);
  lineB.SetLineWidth(1);
  lineB.SetLineStyle(3);
  lineB.DrawLine(0, 1.05, 100, 1.05);
  lineB.DrawLine(0, 0.95, 100, 0.95);
  CRatio2->SaveAs(Form("%sGl_ImpactMean_%s_%s_%s_test.png", outDir, model0, energ0, sys));
  // CRatio2->SaveAs(Form("/home/dim/Work/FIT/dataNEW/FITplot/GlauberFitmean_%s_%s_%sTEST.png", model0, energ0, sys));

  GrFitMult->SetMarkerStyle(MStyleGl[0]);
  GrFitMult->SetMarkerColor(MColor[1]);
  GrFitMult->SetMarkerSize(MSizeGl[0]);
  GrFitMult->SetLineColorAlpha(MColor[1], 1);
  GrFitMult->SetLineWidth(2);
  // GrFitMult->SetNpx(n1bins);
  GrDataMult->SetMarkerStyle(MStyleData[0]);
  GrDataMult->SetMarkerSize(MSizeData[0]);
  GrDataMult->SetLineWidth(2);
  GrDataMult->SetLineColorAlpha(1, 1);
  GrDataMult->GetXaxis()->SetLimits(0, Nn);
  GrDataMult->GetXaxis()->SetNdivisions(509);
  GrDataMult->GetYaxis()->SetRangeUser(0.5, 20000000);
  GrDataMult->SetTitle("");
  GrDataMult->GetXaxis()->SetTitle("N_{ch}");
  GrDataMult->GetYaxis()->SetTitle("dN/dN_{ch}");

  GrDataMult->GetYaxis()->SetTitleSize(25);
  GrDataMult->GetYaxis()->SetTitleFont(43);
  GrDataMult->GetYaxis()->SetTitleOffset(1.9);
  // GrDataMult->GetYaxis()->CenterTitle(true);
  GrDataMult->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  GrDataMult->GetYaxis()->SetLabelSize(25);
  GrDataMult->GetYaxis()->SetLabelOffset(0.018);

  // GrDataMult->GetXaxis()->CenterTitle(true);
  GrDataMult->GetXaxis()->SetTitleSize(25);
  GrDataMult->GetXaxis()->SetTitleFont(43);
  GrDataMult->GetXaxis()->SetTitleOffset(2.65);
  GrDataMult->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  GrDataMult->GetXaxis()->SetLabelSize(25);
  GrDataMult->GetXaxis()->SetLabelOffset(0.035);
  // GrDataMult->GetXaxis()->SetTickLength(0.08);

  TGraphErrors *RatioUrFit;
  RatioUrFit = RatioGr(GrFitMult, GrDataMult, 0, 0.65, Nn, 1.35, true);
  RatioUrFit->GetXaxis()->SetTitle("N_{ch}");
  RatioUrFit->GetYaxis()->SetTitle("MC-Gl/Model");
  RatioUrFit->SetTitle("");
  RatioUrFit->GetYaxis()->SetTitleSize(25);
  RatioUrFit->GetYaxis()->SetTitleFont(43);
  RatioUrFit->GetYaxis()->SetTitleOffset(2);
  RatioUrFit->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  RatioUrFit->GetYaxis()->SetLabelSize(25);
  RatioUrFit->GetYaxis()->SetLabelOffset(0.03);
  RatioUrFit->GetYaxis()->CenterTitle(true);
  //  RatioUrFit->GetXaxis()->CenterTitle(true);
  RatioUrFit->GetYaxis()->SetNdivisions(504);
  RatioUrFit->GetXaxis()->SetNdivisions(509);
  RatioUrFit->GetXaxis()->SetTitleSize(25);
  RatioUrFit->GetXaxis()->SetTitleFont(43);
  RatioUrFit->GetXaxis()->SetTitleOffset(1.4);
  RatioUrFit->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  RatioUrFit->GetXaxis()->SetLabelSize(25);
  RatioUrFit->GetXaxis()->SetLabelOffset(0.035);
  RatioUrFit->GetXaxis()->SetTickLength(0.08);
  /*RatioUrFit->SetMarkerStyle(MStyleFit[0]);
  RatioUrFit->SetMarkerSize(MSizeFit[0]);
  RatioUrFit->SetLineWidth(2);
  RatioUrFit->SetLineColorAlpha(MColor[2], 1);
  RatioUrFit->SetMarkerColor(MColor[2]);*/
  RatioUrFit->SetLineColorAlpha(MColor[1], 1);
  RatioUrFit->SetLineWidth(2);

  TCanvas *c = new TCanvas("Mean", "Mean", 800, 800);
  float ratY = 0.35, ratx = 1;
  TPad *pad[4];

  pad[0] = new TPad("pad22", "pad22", 0.0, 0, ratx, ratY);
  pad[1] = new TPad("pad22", "pad22", 0.0, ratY, ratx, 1);
  pad[2] = new TPad("pad22", "pad22", 0, 0, 1, ratY);
  pad[3] = new TPad("pad22", "pad22", 0, ratY, 1, 1);

  c->cd();
  pad[0]->SetBottomMargin(0.3);
  pad[0]->SetTopMargin(0.0);
  pad[0]->SetLeftMargin(0.12);
  pad[0]->SetRightMargin(0.03);
  pad[0]->Draw();
  pad[0]->cd();
  RatioUrFit->Draw("AP");
  TLine line;
  line.SetLineWidth(2);
  line.SetLineStyle(2);
  line.DrawLine(0, 1, Nn, 1);

  pad[1]->SetBottomMargin(0.0);
  pad[1]->SetTopMargin(0.05);
  pad[1]->SetLeftMargin(0.12);
  pad[1]->SetRightMargin(0.03);
  c->cd();
  pad[1]->Draw();
  pad[1]->cd();
  pad[1]->cd()->SetLogy();

  CutHisto(Data0_10, binNch[0], binNchMax[1]);
  //CutHisto(Data0_10, binNch[1], binNchMax[0]);
  Data0_10->SetFillColor(kWhite);
  Data0_10->SetLineColor(kGray + 1);

  CutHisto(Data10_40, binNchMax[1], binNchMax[7]);
  //CutHisto(Data10_40, binNch[7], binNch[1]);
  Data10_40->SetFillColor(kGray + 1);
  Data10_40->SetFillStyle(3003);
  Data10_40->SetLineColor(kGray + 1);
  
  CutHisto(Data40_80, binNchMax[7], binNchMax[11]);
  //CutHisto(Data40_80, binNch[11], binNch[7]);
  Data40_80->SetFillColor(kGray + 5);
  Data40_80->SetFillStyle(3002);
  Data40_80->SetLineColor(kGray + 1);

  GrDataMult->Draw("AP");

  // Data0_10->Draw("SAME H");
  Data10_40->Draw("SAME H");
  Data40_80->Draw("SAME H");
  GrDataMult->Draw("SAME P");
  GrFitMult->Draw("SAME P");
  
  

  TLatex FitResultText0;
  FitResultText0.SetTextAlign(12);
  FitResultText0.SetTextSize(0.035);
  FitResultText0.SetTextFont(62);
  FitResultText0.DrawLatex(0.05 * Nn, 5000000, Form("#chi^{2}/ndf=%0.2f", chi2));
  TLatex FitResultText;
  FitResultText.SetTextAlign(12);
  FitResultText.SetTextSize(0.035);
  FitResultText.SetTextFont(42);
  // FitResultText.DrawLatex(0.05 * Nn, 5000000, Form("#chi^{2}/ndf=%0.2f", chi2 / NDF));
  FitResultText.DrawLatex(0.05 * Nn, 2000000, Form("f=%0.2f, #mu=%0.2f, k=%0.0f", f, mu, k));
  FitResultText.DrawLatex(0.05 * Nn, 500000, "P_{#mu,k}#times[fN_{part}+(1-f)N_{cool}]");

  TLegend *legdif1 = new TLegend(0.8, 0.6, 0.95, 0.91);
  legdif1->SetBorderSize(0);
  legdif1->AddEntry(GrDataMult, "Model", "p");
  legdif1->AddEntry(GrFitMult, "MC-Gl", "p");
  legdif1->AddEntry(Data0_10, "0-10%", "f");
  legdif1->AddEntry(Data10_40, "10-40%", "f");
  legdif1->AddEntry(Data40_80, "40-80%", "f");
  legdif1->SetTextSize(0.035);
  legdif1->Draw();
  ptB->Draw();

  line.SetLineWidth(2);
  line.SetLineStyle(1);

  // Read TTree
  TLatex latex;
  latex.SetTextAlign(12);
  latex.SetTextSize(0.04);
  latex.SetTextFont(42);
  latex.SetTextAngle(90);

  for (int i = 0; i < Nclasses; i++)
  {
    Result->GetEntry(i);
    line.DrawLine(binNchMax[i], 0, binNchMax[i], GlaubV[i]);
    // cout << endl   << "cent=" << i << " ,bin=" << binNch[i];
    IntMaxC = (int)MaxPercent;
    IntMinC = (int)MinPercent;

    if (i == 0)
    {
      latex.DrawLatex(MinBorder + 0.2 * (MaxBorder - MinBorder), 0.5 * sqrt(GlaubV[0]), Form("%d-%d%s", IntMinC, IntMaxC, "%"));
    }

    else if (i > 0 && i < 5)
    {
      latex.DrawLatex(0.5 * (MinBorder + MaxBorder), 0.5 * sqrt(GlaubV[0]), Form("%d-%d%s", IntMinC, IntMaxC, "%"));
    }

    else if (i > 4 && i < 6)
      //else if (i > 7 && i < 9)
    {
      latex.DrawLatex(0.5 * (MinBorder + MaxBorder), 0.5 * sqrt(GlaubV[0]), Form("%d-%d%s", IntMinC, IntMaxC, "%"));
    }
    if (i > 6)
    {
      line.SetLineStyle(2);
    }
  }

  c->SaveAs(Form("%sGlFit_%s_%s_%s_test.png", outDir, model0, energ0, sys));
  // c->SaveAs(Form("/home/dim/Work/FIT/dataNEW/FITplot/GlauberFit_%s%s_%s_TEST.png", model0, energ0, sys));
}
