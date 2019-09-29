void CentralityClasses(Int_t CentralityClasses){
	TFile *f1 = new TFile("/home/segal/NICA/NICA/centrality-master/build/Result/HistoCutResult_11GeV.root");
	TFile *f5 = new TFile("/home/segal/NICA/NICA/centrality-master/build/Result/glauber_qa_11GeV.root");
	TTree *Borders=(TTree*)f1->Get("Borders");
	
	TFile *fOut   = new TFile("FINAL.root", "recreate");
	TTree *Result=new TTree("Result", "Result");
	TH2D  *B_VS_Multiplicity     = (TH2D*)f5->Get("B_VS_Multiplicity");
	TH2D  *Npart_VS_Multiplicity = (TH2D*)f5->Get("Npart_VS_Multiplicity");
	TH2D  *Ncoll_VS_Multiplicity = (TH2D*)f5->Get("Ncoll_VS_Multiplicity");

	B_VS_Multiplicity     -> SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity -> SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity -> SetBit(TH1::kNoStats);

	Int_t Ncc, MinBorder, MaxBorder, MinBorder_R, MaxBorder_R;
	Float_t MinPercent, MaxPercent, B, Npart, Ncoll, NprotonsA; 
	double B_av, Npart_av, Ncoll_av;
	double RMS_B_av, RMS_Npart_av, RMS_Ncoll_av;
	float mu, f, k, chi2, chi2_error;
	
	Borders -> SetBranchAddress("MinBorder", &MinBorder);
	Borders -> SetBranchAddress("MaxBorder", &MaxBorder);
	Int_t entries=(Int_t)Borders->GetEntries();

	Result -> Branch("Ncc", &Ncc);
	Result -> Branch("MinPercent", &MinPercent);
	Result -> Branch("MaxPercent", &MaxPercent);
	Result -> Branch("MinBorder", &MinBorder_R);
	Result -> Branch("MaxBorder", &MaxBorder_R);

        TH1D* B_VS_CentralityHisto[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto[i] = new TH1D(Form("B_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto[i] -> SetBit(TH1::kNoStats);

        TH1D* Npart_VS_CentralityHisto[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto[i] = new TH1D(Form("Npart_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto[i] -> SetBit(TH1::kNoStats);

        TH1D* Ncoll_VS_CentralityHisto[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto[i] = new TH1D(Form("Ncoll_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";Ncoll;counts", 1000, 0, 1000);
	for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto[i] -> SetBit(TH1::kNoStats);

        TH1D* B_average_VS_Centrality     = new TH1D("B_average_VS_Centrality", ";Centrality, %;B, fm;", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality = new TH1D("Npart_average_VS_Centrality", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality = new TH1D("Ncoll_average_VS_Centrality", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);

        B_average_VS_Centrality     -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality -> SetBit(TH1::kNoStats);

	B_average_VS_Centrality     -> SetLineColor(kBlack);
	Npart_average_VS_Centrality -> SetLineColor(kBlack);
	Ncoll_average_VS_Centrality -> SetLineColor(kBlack);
	
	B_average_VS_Centrality     -> SetLineWidth(1);
	Npart_average_VS_Centrality -> SetLineWidth(1);
	Ncoll_average_VS_Centrality -> SetLineWidth(1);

	B_average_VS_Centrality     -> SetMarkerStyle(20);
	Npart_average_VS_Centrality -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality -> SetMarkerStyle(20);

	B_average_VS_Centrality     -> SetMarkerSize(5);
	Npart_average_VS_Centrality -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality -> SetMarkerSize(5);

	B_average_VS_Centrality     -> SetMarkerColor(kBlack);
	Npart_average_VS_Centrality -> SetMarkerColor(kBlack);
	Ncoll_average_VS_Centrality -> SetMarkerColor(kBlack);

	B_average_VS_Centrality     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality -> GetXaxis() -> SetNdivisions (10, kTRUE);

	B_VS_CentralityHisto[CentralityClasses]     = B_VS_Multiplicity->ProjectionY("B_VS_CentralityClass 0%-100%", 0, 10000);
	Npart_VS_CentralityHisto[CentralityClasses] = Npart_VS_Multiplicity->ProjectionY("Npart_VS_CentralityClass 0%-100%", 0, 10000);
	Ncoll_VS_CentralityHisto[CentralityClasses] = Ncoll_VS_Multiplicity->ProjectionY("Ncoll_VS_CentralityClass 0%-100%", 0, 10000);
       	for (int i=0; i<entries; i++) {
		Borders -> GetEntry(i);
		B_VS_CentralityHisto[i]     = B_VS_Multiplicity->ProjectionY(Form("B_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder, MaxBorder);
		Npart_VS_CentralityHisto[i] = Npart_VS_Multiplicity->ProjectionY(Form("Npart_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder, MaxBorder);
		Ncoll_VS_CentralityHisto[i] = Ncoll_VS_Multiplicity->ProjectionY(Form("Ncoll_VS_CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder, MaxBorder);
		}

	int j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		B_VS_CentralityHisto[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) B_VS_CentralityHisto[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {B_VS_CentralityHisto[i] -> SetXTitle("B, fm"); B_VS_CentralityHisto[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Npart_VS_CentralityHisto[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Npart_VS_CentralityHisto[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Npart_VS_CentralityHisto[i] -> SetXTitle("N_{part}"); Npart_VS_CentralityHisto[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Ncoll_VS_CentralityHisto[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Ncoll_VS_CentralityHisto[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Ncoll_VS_CentralityHisto[i] -> SetXTitle("N_{coll}"); Ncoll_VS_CentralityHisto[i] -> SetYTitle("counts");}
	
	for (int i = 0; i < CentralityClasses; i++) {
		cout<<i<<endl;
		Ncc=i+1;
		MinPercent=(i)*100/CentralityClasses;
		MaxPercent=(i+1)*100/CentralityClasses;
		
		Borders -> GetEntry(i);

		MinBorder_R=MinBorder;
		MaxBorder_R=MaxBorder;

		B_av=B_VS_CentralityHisto[i]->GetMean();
		Npart_av=Npart_VS_CentralityHisto[i]->GetMean();
		Ncoll_av=Ncoll_VS_CentralityHisto[i]->GetMean();

		RMS_B_av=B_VS_CentralityHisto[i]->GetRMS();
		RMS_Npart_av=Npart_VS_CentralityHisto[i]->GetRMS();
		RMS_Ncoll_av=Ncoll_VS_CentralityHisto[i]->GetRMS();
	
		B_average_VS_Centrality     -> SetBinContent(i+1,B_av);
		Npart_average_VS_Centrality -> SetBinContent(i+1,Npart_av);
		Ncoll_average_VS_Centrality -> SetBinContent(i+1,Ncoll_av);

		B_average_VS_Centrality     -> SetBinError(i+1,RMS_B_av);
		Npart_average_VS_Centrality -> SetBinError(i+1,RMS_Npart_av);
		Ncoll_average_VS_Centrality -> SetBinError(i+1,RMS_Ncoll_av);

		Result->Fill();
		}

	TCanvas* c1 = new TCanvas("B_VS_Centrality","B_VS_Centrality", 1500, 900);
	TLegend legend1(0.75,0.75,1.0,1.0, "B VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend1.AddEntry(B_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend1.AddEntry(B_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto[i]->Draw("same");
	legend1.Draw("same");
	c1->Write();
	for (int i = 0; i <= CentralityClasses; i++) B_VS_CentralityHisto[i] -> Write();
	c1->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality.pdf");
	c1->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality.C");

	TCanvas* c2 = new TCanvas("Npart_VS_Centrality","Npart_VS_Centrality", 1500, 900);
	c2->SetLogy();
	TLegend legend2(0.75,0.75,1.0,1.0, "N_{part} VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend2.AddEntry(Npart_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend2.AddEntry(Npart_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto[i]->Draw("same");
	legend2.Draw("same");
	c2->Write();
	for (int i = 0; i <= CentralityClasses; i++) Npart_VS_CentralityHisto[i] -> Write();
	c2->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality.pdf");
	c2->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality.C");

	TCanvas* c3 = new TCanvas("Ncoll_VS_Centrality","Ncoll_VS_Centrality", 1500, 900);
	c3->SetLogy();
	TLegend legend3(0.75,0.75,1.0,1.0, "N_{coll} VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend3.AddEntry(Ncoll_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend3.AddEntry(Ncoll_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto[i]->Draw("same");
	legend3.Draw("same");
	c3->Write();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto[i] -> Write();
	c3->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality.pdf");
	c3->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality.C");	

	TCanvas* c13 = new TCanvas("B_average_VS_Centrality","B_average_VS_Centrality", 1500, 900);
	TLegend legend13(0.1,0.75,0.35,1.0, "<B> VS Centrality");
	legend13.AddEntry(B_average_VS_Centrality, "<B> VS Centrality");
	B_average_VS_Centrality -> Draw("E1, P, X0");
	legend13.Draw("same");
	c13->Write();
	c13->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality_Result.pdf");
	c13->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality_Result.C");

	TCanvas* c14 = new TCanvas("Npart_average_VS_Centrality","Npart_average_VS_Centrality", 1500, 900);
	TLegend legend14(0.75,0.75,1.0,1.0, "<N_{part}> VS Centrality");
	legend14.AddEntry(Npart_average_VS_Centrality, "<N_{part}> VS Centrality");
	Npart_average_VS_Centrality -> Draw("E1, P, X0");
	legend14.Draw("same");
	c14->Write();
	c14->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality_Result.pdf");
	c14->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality_Result.C");

	TCanvas* c15 = new TCanvas("Ncoll_average_VS_Centrality","Ncoll_average_VS_Centrality", 1500, 900);
	TLegend legend15(0.75,0.75,1.0,1.0, "<N_{coll}> VS Centrality");
	legend15.AddEntry(Ncoll_average_VS_Centrality, "<N_{coll}> VS Centrality");
	Ncoll_average_VS_Centrality -> Draw("E1, P, X0");
	legend15.Draw("same");
	c15->Write();
	c15->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality_Result.pdf");
	c15->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality_Result.C");
	
	TCanvas* c16 = new TCanvas("B_VS_Centrality","B_VS_Centrality", 3000, 1800);
	TLegend legend16(0.75,0.75,1.0,1.0, "B VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend16.AddEntry(B_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend16.AddEntry(B_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto[i]->Draw("same");
	legend16.Draw("same");
	c16->cd();
	c16->Write();
	c16->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality.pdf");
	c16->SaveAs("/home/segal/NICA/NICA/11GeV/B_VS_Centrality.C");

	std::unique_ptr <TCanvas> c17 {new TCanvas("Npart_VS_Centrality","N_{part} VS Centrality", 3000, 1800)};
	gPad->SetLogy();
	TLegend legend17(0.75,0.75,1.0,1.0, "N_{part} VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend17.AddEntry(Npart_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend17.AddEntry(Npart_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto[i]->Draw("same");
	legend17.Draw("same");
	c17->Write();
	c17->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality.pdf");
	c17->SaveAs("/home/segal/NICA/NICA/11GeV/Npart_VS_Centrality.C");

	std::unique_ptr <TCanvas> c18 {new TCanvas("Ncoll_VS_Centrality","N_{coll}_VS_Centrality", 3000, 1800)};
	gPad->SetLogy();
	TLegend legend18(0.75,0.75,1.0,1.0, "N_{coll} VS Centrality");
	for (int i = 0; i < CentralityClasses; i++) legend18.AddEntry(Ncoll_VS_CentralityHisto[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend18.AddEntry(Ncoll_VS_CentralityHisto[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto[i]->Draw("same");
	legend18.Draw("same");
	c18->Write();
	c18->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality.pdf");
	c18->SaveAs("/home/segal/NICA/NICA/11GeV/Ncoll_VS_Centrality.C");

	TCanvas* c19 = new TCanvas("Result","", 9000, 2000);
	c19->Divide(3,1);
	c19->cd(1);
	TLegend legend1913(0.1,0.75,0.35,1.0, "<B> VS Centrality");
	legend1913.AddEntry(B_average_VS_Centrality, "<B> VS Centrality");
	B_average_VS_Centrality -> Draw("E1, P, X0");
	legend1913.Draw("same");
	c19->cd(2);
	TLegend legend1914(0.75,0.75,1.0,1.0, "<N_{part}> VS Centrality");
	legend1914.AddEntry(Npart_average_VS_Centrality, "<N_{part}> VS Centrality");
	Npart_average_VS_Centrality -> Draw("E1, P, X0");
	legend1914.Draw("same");
	c19->cd(3);
	TLegend legend1915(0.75,0.75,1.0,1.0, "<N_{coll}> VS Centrality");
	legend1915.AddEntry(Ncoll_average_VS_Centrality, "<N_{coll}> VS Centrality");
	Ncoll_average_VS_Centrality -> Draw("E1, P, X0");
	legend1915.Draw("same");
	c19->Write();
	c19->SaveAs("/home/segal/NICA/NICA/11GeV/Result.pdf");
	c19->SaveAs("/home/segal/NICA/NICA/11GeV/Result.C");

	B_average_VS_Centrality     -> Write();
	Npart_average_VS_Centrality -> Write();
	Ncoll_average_VS_Centrality -> Write();
	
	Result->Write();

	fOut->Close();
}
