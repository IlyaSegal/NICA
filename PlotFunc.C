
double Scale(TH1F *HistTrue, TH1F *Hist)
{
    TF1 *f1 = new TF1("f1", "gausn", 0.75 * HistTrue->FindLastBinAbove(), 0.98 * HistTrue->FindLastBinAbove());
    HistTrue->Fit(f1, "RMN");
    double MaxX1 = f1->GetParameter(1) + 3 * f1->GetParameter(2);

    TF1 *f2 = new TF1("f2", "gausn", 0.75 * Hist->FindLastBinAbove(), 0.98 * Hist->FindLastBinAbove());
    Hist->Fit(f2, "RMN");
    double MaxX2 = f2->GetParameter(1) + 3 * f2->GetParameter(2);
    cout << "MaxX2 / MaxX1 " << MaxX2 / MaxX1 << endl;
    return MaxX2 / MaxX1;
}

TGraphErrors *HistGraph(TH1F *Hist, double scaleX = 1, double scaleY = 1)
{
    const int Nbin = Hist->FindLastBinAbove();
    Double_t vx_gr[Nbin], vy_gr[Nbin], ex_gr[Nbin], ey_gr[Nbin];
    // TGraphErrors *gr = new TGraphErrors(Nbin, vx_gr, vy_gr, ex_gr, ey_gr);
    for (int i = 0; i < Nbin; i++)
    {
        vx_gr[i] = Hist->GetBinCenter(i + 1) / scaleX;
        vy_gr[i] = Hist->GetBinContent(i + 1) / scaleY;
        ex_gr[i] = 0;
        ey_gr[i] = Hist->GetBinError(i + 1);
    }
    // TGraph *gr = new TGraph(Nbin, vx_gr, vy_gr);
    TGraphErrors *gr = new TGraphErrors(Nbin, vx_gr, vy_gr, ex_gr, ey_gr);

    return gr;
}

TGraphErrors *RatioGr(TGraphErrors *const &gr1, TGraphErrors *const &gr2, double Xmin, double Ymin, double Xmax, double Ymax, bool Error = true)
{
    // Read points
    Double_t *vx_gr1 = gr1->GetX();
    Double_t *vy_gr1 = gr1->GetY();
    Double_t *vx_gr2 = gr2->GetX();
    Double_t *vy_gr2 = gr2->GetY();
    // Read errors
    Double_t *ex_gr1 = gr1->GetEX();
    Double_t *ey_gr1 = gr1->GetEY();
    Double_t *ex_gr2 = gr2->GetEX();
    Double_t *ey_gr2 = gr2->GetEY();

    int n1bins = gr1->GetN();
    int n2bins = gr2->GetN();

    Color_t GrColor = gr1->GetMarkerColor();
    Style_t GrStyle = gr1->GetMarkerStyle();
    Size_t GrSize = gr1->GetMarkerSize();

    if (n2bins < n1bins)
    {
        n1bins = n2bins;
    }
    Double_t vx_gr3[n1bins], vy_gr3[n1bins], ex_gr3[n1bins], ey_gr3[n1bins];
    for (int i = 0; i < n1bins; i++)
    {
        vx_gr3[i] = vx_gr1[i];
        ex_gr3[i] = ex_gr1[i];
        vy_gr3[i] = vy_gr1[i] / vy_gr2[i];
        ey_gr3[i] = sqrt(pow(ey_gr1[i] / vy_gr2[i], 2) + pow(vy_gr1[i] * ey_gr2[i] / (vy_gr2[i] * vy_gr2[i]), 2));
        if (!Error)
        {
            ey_gr3[i] = 0;
        }
    }

    TGraphErrors *grRatio = new TGraphErrors(n1bins, vx_gr3, vy_gr3, ex_gr3, ey_gr3);
    grRatio->GetXaxis()->SetLimits(Xmin, Xmax);
    grRatio->GetYaxis()->SetRangeUser(Ymin, Ymax);
    grRatio->SetMarkerColor(GrColor);
    grRatio->SetMarkerStyle(GrStyle);
    grRatio->SetMarkerSize(GrSize);

    return grRatio;
}

TGraphErrors *RatioGr2(TGraphErrors *const &gr1, TGraphErrors *const &gr2, double Xmin, double Ymin, double Xmax, double Ymax, bool Error = true)
{
    // Read points
    Double_t *vx_gr1 = gr1->GetX();
    Double_t *vy_gr1 = gr1->GetY();
    Double_t *vx_gr2 = gr2->GetX();
    Double_t *vy_gr2 = gr2->GetY();
    // Read errors
    Double_t *ex_gr1 = gr1->GetEX();
    Double_t *ey_gr1 = gr1->GetEY();
    Double_t *ex_gr2 = gr2->GetEX();
    Double_t *ey_gr2 = gr2->GetEY();

    int n1bins = gr1->GetN();
    int n2bins = gr2->GetN();

    Color_t GrColor = gr1->GetMarkerColor();
    Style_t GrStyle = gr1->GetMarkerStyle();
    Size_t GrSize = gr1->GetMarkerSize();

    if (n2bins < n1bins)
    {
        n1bins = n2bins;
    }
    Double_t vx_gr3[n1bins], vy_gr3[n1bins], ex_gr3[n1bins], ey_gr3[n1bins];
    for (int i = 0; i < n1bins; i++)
    {
        vx_gr3[i] = vx_gr1[i];
        ex_gr3[i] = ex_gr1[i];
        vy_gr3[i] = vy_gr1[i] / vy_gr2[i];
        ey_gr3[i] = 0;
        if (!Error)
        {
            ey_gr3[i] = 0;
        }
    }

    TGraphErrors *grRatio = new TGraphErrors(n1bins, vx_gr3, vy_gr3, ex_gr3, ey_gr3);
    grRatio->GetXaxis()->SetLimits(Xmin, Xmax);
    grRatio->GetYaxis()->SetRangeUser(Ymin, Ymax);
    grRatio->SetMarkerColor(GrColor);
    grRatio->SetMarkerStyle(GrStyle);
    grRatio->SetMarkerSize(GrSize);

    return grRatio;
}

TGraphErrors *RatioGr(TGraphErrors *const &gr1, TF1 *func, double Xmin, double Ymin, double Xmax, double Ymax)
{
    // Read points
    Double_t *vx_gr1 = gr1->GetX();
    Double_t *vy_gr1 = gr1->GetY();
    // Read errors
    Double_t *ex_gr1 = gr1->GetEX();
    Double_t *ey_gr1 = gr1->GetEY();
    Double_t funcVak;
    int n1bins = gr1->GetN();
    Double_t vx_gr3[n1bins], vy_gr3[n1bins], ex_gr3[n1bins], ey_gr3[n1bins];
    for (int i = 0; i < n1bins; i++)
    {
        vx_gr3[i] = vx_gr1[i];
        ex_gr3[i] = ex_gr1[i];
        funcVak = func->Eval(vx_gr1[i]);
        vy_gr3[i] = vy_gr1[i] / funcVak;
        ey_gr3[i] = sqrt(pow(ey_gr1[i] / funcVak, 2));
    }

    TGraphErrors *grRatio = new TGraphErrors(n1bins, vx_gr3, vy_gr3, ex_gr3, ey_gr3);

    // grRatio->GetXaxis()->SetLimits(Xmin, Xmax);
    grRatio->GetXaxis()->SetRangeUser(Xmin, Xmax);
    grRatio->GetYaxis()->SetRangeUser(Ymin, Ymax);
    // grRatio->GetYaxis()->SetTitle("V_{2}{4}/V_{2}{2}");
    return grRatio;
}

TGraphErrors *RatioGr(TF1 *func, TGraphErrors *const &gr2, double Xmin, double Ymin, double Xmax, double Ymax)
{
    // Read points
    Double_t *vx_gr2 = gr2->GetX();
    Double_t *vy_gr2 = gr2->GetY();
    // Read errors
    Double_t *ex_gr2 = gr2->GetEX();
    Double_t *ey_gr2 = gr2->GetEY();

    Double_t funcVak;
    int n1bins = gr2->GetN();
    Double_t vx_gr3[n1bins], vy_gr3[n1bins], ex_gr3[n1bins], ey_gr3[n1bins];
    for (int i = 0; i < n1bins; i++)
    {
        vx_gr3[i] = vx_gr2[i];
        ex_gr3[i] = ex_gr2[i];
        funcVak = func->Eval(vx_gr2[i]);
        vy_gr3[i] = funcVak / vy_gr2[i];
        ey_gr3[i] = sqrt(pow(funcVak * ey_gr2[i] / (vy_gr2[i] * vy_gr2[i]), 2));
    }

    TGraphErrors *grRatio = new TGraphErrors(n1bins, vx_gr3, vy_gr3, ex_gr3, ey_gr3);

    grRatio->GetXaxis()->SetLimits(Xmin, Xmax);
    // grRatio->GetXaxis()->SetRangeUser(Xmin, Xmax);
    grRatio->GetYaxis()->SetRangeUser(Ymin, Ymax);
    // grRatio->GetYaxis()->SetTitle("V_{2}{4}/V_{2}{2}");
    return grRatio;
}

TGraphErrors *GrFunc(TF1 *func, TGraphErrors *const &gr2, double Xmin, double Ymin, double Xmax, double Ymax)
{
    // Read points
    Double_t *vx_gr2 = gr2->GetX();
    Double_t *vy_gr2 = gr2->GetY();
    // Read errors
    Double_t *ex_gr2 = gr2->GetEX();
    Double_t *ey_gr2 = gr2->GetEY();

    Double_t funcVak;
    int N0 = 15;
    int n1bins = gr2->GetN();
    Double_t vx_gr3[n1bins], vy_gr3[n1bins], ex_gr3[n1bins], ey_gr3[n1bins];
    for (int i = 0; i < n1bins; i++)
    {
        vx_gr3[i] = N0;
        ex_gr3[i] = ex_gr2[i];
        funcVak = func->Eval(vx_gr3[i]);
        vy_gr3[i] = funcVak;
        // cout<<"x"<<i<<"="<< vx_gr2[i+N0]<<" y="<<funcVak<<endl;

        N0 += 4;
        ey_gr3[i] = 0;
    }

    TGraphErrors *grRatio = new TGraphErrors(n1bins, vx_gr3, vy_gr3, ex_gr3, ey_gr3);

    grRatio->GetXaxis()->SetLimits(Xmin, Xmax);
    // grRatio->GetXaxis()->SetRangeUser(Xmin, Xmax);
    grRatio->GetYaxis()->SetRangeUser(Ymin, Ymax);
    // grRatio->GetYaxis()->SetTitle("V_{2}{4}/V_{2}{2}");
    return grRatio;
}

void Style(TGraphErrors *const &gr, Color_t Color, const int MStyle, const char *YTitle = "fit/data", const char *XTitle = "N_{ch}", const int TextSize = 34, const double MarkSize = 1.5)
{
    gr->GetXaxis()->SetTitle(XTitle);
    gr->GetYaxis()->SetTitle(YTitle);
    gr->SetTitle("");
    gr->GetYaxis()->SetTitleSize(TextSize);
    gr->GetYaxis()->SetTitleFont(63);
    gr->GetYaxis()->SetTitleOffset(3);
    gr->GetYaxis()->SetLabelFont(63); // Absolute font size in pixel (precision 3)
    gr->GetYaxis()->SetLabelSize(TextSize);
    gr->GetYaxis()->SetLabelOffset(0.040);
    gr->GetYaxis()->CenterTitle(true);
    gr->GetYaxis()->SetNdivisions(505);

    gr->GetXaxis()->SetNdivisions(505);
    gr->GetXaxis()->SetTitleSize(TextSize);
    gr->GetXaxis()->SetTitleFont(63);
    gr->GetXaxis()->SetTitleOffset(4);
    gr->GetXaxis()->SetLabelFont(63); // Absolute font size in pixel (precision 3)
    gr->GetXaxis()->SetLabelSize(TextSize);
    gr->GetXaxis()->SetLabelOffset(0.035);
    gr->GetXaxis()->SetTickLength(0.08);
    gr->GetXaxis()->CenterTitle(true);
    gr->SetMarkerStyle(MStyle);
    gr->SetMarkerSize(MarkSize);
    gr->SetLineWidth(1);
    gr->SetLineColorAlpha(Color, 1);
    gr->SetMarkerColor(Color);
}

void TpadStyle(TPad *TP, const double Up, const double Dw, const double Lf, const double Rg)
{
    TP->SetTopMargin(Up);
    TP->SetBottomMargin(Dw);
    TP->SetLeftMargin(Lf);
    TP->SetRightMargin(Rg);
}

void CutHisto(TH1F *histo, int xmin, int xmax)
{
    // Look for the number of bins of the histogram
    int Nbins = histo->GetNbinsX();
    // fill hitograms (!! bin content is +1 ahead !!)
    for (int i = 0; i < Nbins; i++)
    {
        // test to see if we are in a region that should be cut
        double x = histo->GetXaxis()->GetBinCenter(i);

        if ((x <= xmin) || (xmax <= x))
        {
            histo->SetBinContent(i, 0.0);
            histo->SetBinError(i, 0.0);
        }
    }
    /*
    for (int i = xmin+1; i < xmax+1; i++)
    {
        histo->SetBinContent(i, 0.0);
        histo->SetBinError(i, 0.0);
    }*/
}