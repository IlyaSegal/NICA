enum eCentralityEstimator {
        kTOFRPC                          =  0,
        kTOF                                 ,
        kRPC                                 ,
        kMDC                                 ,
	kFW                                  ,
        kCentralityEstimator              
    };

TString CentralityEstimatorName[kCentralityEstimator]=
    {
        "hitsTOF+RPC"                         ,
        "hitsTOF"                             ,
        "hitsRPC"                             ,
        "tracksMDC"                           ,
	"FWSumChargeZ"
    };

void CentralityClasses(Int_t CentralityClasses){
	TFile *f1 = new TFile("/home/vad/centrality/build/Result/HistoCutResult_TOF.root");
	TFile *f2 = new TFile("/home/vad/centrality/build/Result/HistoCutResult_RPC.root");
	TFile *f3 = new TFile("/home/vad/centrality/build/Result/HistoCutResult_MDC.root");
	TFile *f4 = new TFile("/home/vad/centrality/build/Result/HistoCutResult_FW.root");
	TFile *f5 = new TFile("/home/vad/centrality/build/Result/glauber_qa_TOF.root");
	TFile *f6 = new TFile("/home/vad/centrality/build/Result/glauber_qa_RPC.root");
	TFile *f7 = new TFile("/home/vad/centrality/build/Result/glauber_qa_MDC.root");
	TFile *f8 = new TFile("/home/vad/centrality/build/Result/glauber_qa_FW_1.root");
	TFile *fOut   = new TFile("FINAL.root", "recreate");
	TTree *Result=new TTree("Result", "Result");
	TTree *Borders_TOF=(TTree*)f1->Get(Form("Borders_%s", CentralityEstimatorName[1].Data()));
	TTree *Borders_RPC=(TTree*)f2->Get(Form("Borders_%s", CentralityEstimatorName[2].Data()));
	TTree *Borders_MDC=(TTree*)f3->Get(Form("Borders_%s", CentralityEstimatorName[3].Data()));
	TTree *Borders_FW=(TTree*)f4->Get(Form("Borders_%s", CentralityEstimatorName[4].Data()));
	TH2D  *B_VS_Multiplicity_TOF     = (TH2D*)f5->Get("B_VS_Multiplicity");
	TH2D  *Npart_VS_Multiplicity_TOF = (TH2D*)f5->Get("Npart_VS_Multiplicity");
	TH2D  *Ncoll_VS_Multiplicity_TOF = (TH2D*)f5->Get("Ncoll_VS_Multiplicity");
	TH2D  *B_VS_Multiplicity_RPC     = (TH2D*)f6->Get("B_VS_Multiplicity");
	TH2D  *Npart_VS_Multiplicity_RPC = (TH2D*)f6->Get("Npart_VS_Multiplicity");
	TH2D  *Ncoll_VS_Multiplicity_RPC = (TH2D*)f6->Get("Ncoll_VS_Multiplicity");
	TH2D  *B_VS_Multiplicity_MDC     = (TH2D*)f7->Get("B_VS_Multiplicity");
	TH2D  *Npart_VS_Multiplicity_MDC = (TH2D*)f7->Get("Npart_VS_Multiplicity");
	TH2D  *Ncoll_VS_Multiplicity_MDC = (TH2D*)f7->Get("Ncoll_VS_Multiplicity");
	TH2D  *B_VS_Multiplicity_FW      = (TH2D*)f8->Get("B_VS_Multiplicity");
	TH2D  *Npart_VS_Multiplicity_FW  = (TH2D*)f8->Get("Npart_VS_Multiplicity");
	TH2D  *Ncoll_VS_Multiplicity_FW  = (TH2D*)f8->Get("Ncoll_VS_Multiplicity");

	B_VS_Multiplicity_TOF     -> SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity_TOF -> SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity_TOF -> SetBit(TH1::kNoStats);
	B_VS_Multiplicity_RPC     -> SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity_RPC -> SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity_RPC -> SetBit(TH1::kNoStats);
	B_VS_Multiplicity_MDC     -> SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity_MDC -> SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity_MDC -> SetBit(TH1::kNoStats);
	B_VS_Multiplicity_FW      -> SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity_FW  -> SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity_FW  -> SetBit(TH1::kNoStats);


	Int_t Ncc, MinBorder_TOF, MaxBorder_TOF,  MinBorder_RPC, MaxBorder_RPC, MinBorder_MDC, MaxBorder_MDC, MinBorder_TOF_R, MaxBorder_TOF_R,  MinBorder_RPC_R, MaxBorder_RPC_R, MinBorder_MDC_R, MaxBorder_MDC_R, MinBorder_FW_R, MaxBorder_FW_R; 
	Int_t MinBorder_FW, MaxBorder_FW;
	Float_t MinPercent, MaxPercent, B, Npart, Ncoll, NprotonsA; 
	double B_av, Npart_av, Ncoll_av, B_TOF_av, Npart_TOF_av, Ncoll_TOF_av, B_RPC_av, Npart_RPC_av, Ncoll_RPC_av, B_MDC_av, Npart_MDC_av, Ncoll_MDC_av, B_FW_av, Npart_FW_av, Ncoll_FW_av;
	double RMS_B_av, RMS_Npart_av, RMS_Ncoll_av, RMS_B_TOF_av, RMS_Npart_TOF_av, RMS_Ncoll_TOF_av, RMS_B_RPC_av, RMS_Npart_RPC_av, RMS_Ncoll_RPC_av, RMS_B_MDC_av, RMS_Npart_MDC_av, RMS_Ncoll_MDC_av, RMS_B_FW_av, RMS_Npart_FW_av, RMS_Ncoll_FW_av;
	float mu_TOF, f_TOF, k_TOF, alpha_TOF, chi2_TOF, chi2_error_TOF;
	float mu_RPC, f_RPC, k_RPC, alpha_RPC, chi2_RPC, chi2_error_RPC;
	float mu_MDC, f_MDC, k_MDC, alpha_MDC, chi2_MDC, chi2_error_MDC;
	float mu_FW, f_FW, k_FW, alpha_FW, chi2_FW, chi2_error_FW;
	
	Borders_TOF -> SetBranchAddress("MinBorder", &MinBorder_TOF);
	Borders_TOF -> SetBranchAddress("MaxBorder", &MaxBorder_TOF);
	Int_t entries_TOF=(Int_t)Borders_TOF->GetEntries();
	Borders_RPC -> SetBranchAddress("MinBorder", &MinBorder_RPC);
	Borders_RPC -> SetBranchAddress("MaxBorder", &MaxBorder_RPC);
	Int_t entries_RPC=(Int_t)Borders_RPC->GetEntries();
	Borders_MDC -> SetBranchAddress("MinBorder", &MinBorder_MDC);
	Borders_MDC -> SetBranchAddress("MaxBorder", &MaxBorder_MDC);
	Int_t entries_MDC=(Int_t)Borders_MDC->GetEntries();
	Borders_FW  -> SetBranchAddress("MinBorder", &MinBorder_FW);
	Borders_FW  -> SetBranchAddress("MaxBorder", &MaxBorder_FW);
	Int_t entries_FW=(Int_t)Borders_FW->GetEntries();

	Result -> Branch("Ncc", &Ncc);
	Result -> Branch("MinPercent", &MinPercent);
	Result -> Branch("MaxPercent", &MaxPercent);
	Result -> Branch("MinBorder_TOF", &MinBorder_TOF_R);
	Result -> Branch("MaxBorder_TOF", &MaxBorder_TOF_R);
	Result -> Branch("MinBorder_RPC", &MinBorder_RPC_R);
	Result -> Branch("MaxBorder_RPC", &MaxBorder_RPC_R); 
	Result -> Branch("MinBorder_MDC", &MinBorder_MDC_R);
	Result -> Branch("MaxBorder_MDC", &MaxBorder_MDC_R); 
	Result -> Branch("MinBorder_FW", &MinBorder_FW_R);
	Result -> Branch("MaxBorder_FW", &MaxBorder_FW_R);
	Result -> Branch("B_average", &B_av); 
	Result -> Branch("Npart_average", &Npart_av);
	Result -> Branch("Ncoll_average", &Ncoll_av);
	Result -> Branch("B_TOF_average", &B_TOF_av);
	Result -> Branch("Npart_TOF_average", &Npart_TOF_av);
	Result -> Branch("Ncoll_TOF_average", &Ncoll_TOF_av);
	Result -> Branch("B_RPC_average", &B_RPC_av);
	Result -> Branch("Npart_RPC_average", &Npart_RPC_av);
	Result -> Branch("Ncoll_RPC_average", &Ncoll_RPC_av);
	Result -> Branch("B_MDC_average", &B_MDC_av);
	Result -> Branch("Npart_MDC_average", &Npart_MDC_av);
	Result -> Branch("Ncoll_MDC_average", &Ncoll_MDC_av);
	Result -> Branch("B_FW_average", &B_FW_av); 
	Result -> Branch("Npart_FW_average", &Npart_FW_av);
	Result -> Branch("Ncoll_FW_average", &Ncoll_FW_av);
	Result -> Branch("RMS_B_average", &RMS_B_av); 
	Result -> Branch("RMS_Npart_average", &RMS_Npart_av);
	Result -> Branch("RMS_Ncoll_average", &RMS_Ncoll_av);
	Result -> Branch("RMS_B_TOF_average", &RMS_B_TOF_av);
	Result -> Branch("RMS_Npart_TOF_average", &RMS_Npart_TOF_av);
	Result -> Branch("RMS_Ncoll_TOF_average", &RMS_Ncoll_TOF_av);
	Result -> Branch("RMS_B_RPC_average", &RMS_B_RPC_av);
	Result -> Branch("RMS_Npart_RPC_average", &RMS_Npart_RPC_av);
	Result -> Branch("RMS_Ncoll_RPC_average", &RMS_Ncoll_RPC_av);
	Result -> Branch("RMS_B_MDC_average", &RMS_B_MDC_av);
	Result -> Branch("RMS_Npart_MDC_average", &RMS_Npart_MDC_av);
	Result -> Branch("RMS_Ncoll_MDC_average", &RMS_Ncoll_MDC_av);
	Result -> Branch("RMS_B_FW_average", &RMS_B_FW_av); 
	Result -> Branch("RMS_Npart_FW_average", &RMS_Npart_FW_av);
	Result -> Branch("RMS_Ncoll_FW_average", &RMS_Ncoll_FW_av);

        TH1D* B_VS_CentralityHisto_TOF[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_TOF[i] = new TH1D(Form("B_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_TOF[i] -> SetBit(TH1::kNoStats);

        TH1D* Npart_VS_CentralityHisto_TOF[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_TOF[i] = new TH1D(Form("Npart_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_TOF[i] -> SetBit(TH1::kNoStats);

        TH1D* Ncoll_VS_CentralityHisto_TOF[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_TOF[i] = new TH1D(Form("Ncoll_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";Ncoll;counts", 750, 0, 750);
	for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_TOF[i] -> SetBit(TH1::kNoStats);

        TH1D* B_VS_CentralityHisto_RPC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_RPC[i] = new TH1D(Form("B_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_RPC[i] -> SetBit(TH1::kNoStats);

        TH1D* Npart_VS_CentralityHisto_RPC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_RPC[i] = new TH1D(Form("Npart_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_RPC[i] -> SetBit(TH1::kNoStats);

        TH1D* Ncoll_VS_CentralityHisto_RPC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_RPC[i] = new TH1D(Form("Ncoll_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";Ncoll;counts", 750, 0, 750);
	for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_RPC[i] -> SetBit(TH1::kNoStats);

        TH1D* B_VS_CentralityHisto_MDC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_MDC[i] = new TH1D(Form("B_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_MDC[i] -> SetBit(TH1::kNoStats);

        TH1D* Npart_VS_CentralityHisto_MDC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_MDC[i] = new TH1D(Form("Npart_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_MDC[i] -> SetBit(TH1::kNoStats);

        TH1D* Ncoll_VS_CentralityHisto_MDC[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_MDC[i] = new TH1D(Form("Ncoll_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";Ncoll;counts", 750, 0, 750);
	for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_MDC[i] -> SetBit(TH1::kNoStats);

        TH1D* B_VS_CentralityHisto_FW[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_FW[i] = new TH1D(Form("B_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses+1; i++)   B_VS_CentralityHisto_FW[i] -> SetBit(TH1::kNoStats);

        TH1D* Npart_VS_CentralityHisto_FW[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_FW[i] = new TH1D(Form("Npart_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses+1; i++)   Npart_VS_CentralityHisto_FW[i] -> SetBit(TH1::kNoStats);

        TH1D* Ncoll_VS_CentralityHisto_FW[CentralityClasses+1];
        for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_FW[i] = new TH1D(Form("Ncoll_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), ";Ncoll;counts", 750, 0, 750);
	for (int i = 0; i < CentralityClasses+1; i++)   Ncoll_VS_CentralityHisto_FW[i] -> SetBit(TH1::kNoStats);

        TH1D* B_average_VS_Centrality         = new TH1D("B_average_VS_Centrality", ";Centrality, %;B, fm", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality     = new TH1D("Npart_average_VS_Centrality", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality     = new TH1D("Ncoll_average_VS_Centrality", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);
        TH1D* B_average_VS_Centrality_TOF     = new TH1D("B_average_VS_Centrality_TOF", ";Centrality, %;B, fm;", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality_TOF = new TH1D("Npart_average_VS_Centrality_TOF", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality_TOF = new TH1D("Ncoll_average_VS_Centrality_TOF", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);
        TH1D* B_average_VS_Centrality_RPC     = new TH1D("B_average_VS_Centrality_RPC", ";Centrality, %;B, fm", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality_RPC = new TH1D("Npart_average_VS_Centrality_RPC", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality_RPC = new TH1D("Ncoll_average_VS_Centrality_RPC", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);
        TH1D* B_average_VS_Centrality_MDC     = new TH1D("B_average_VS_Centrality_MDC", ";Centrality, %;B, fm", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality_MDC = new TH1D("Npart_average_VS_Centrality_MDC", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality_MDC = new TH1D("Ncoll_average_VS_Centrality_MDC", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);
        TH1D* B_average_VS_Centrality_FW      = new TH1D("B_average_VS_Centrality_FW ", ";Centrality, %;B, fm", CentralityClasses, 0, 100);
        TH1D* Npart_average_VS_Centrality_FW  = new TH1D("Npart_average_VS_Centrality_FW ", ";Centrality, %;N_{part}", CentralityClasses, 0, 100);
        TH1D* Ncoll_average_VS_Centrality_FW  = new TH1D("Ncoll_average_VS_Centrality_FW ", ";Centrality, %;N_{coll}", CentralityClasses, 0, 100);

	B_average_VS_Centrality         -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality     -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality     -> SetBit(TH1::kNoStats);
        B_average_VS_Centrality_TOF     -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality_TOF -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality_TOF -> SetBit(TH1::kNoStats);
        B_average_VS_Centrality_RPC     -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality_RPC -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality_RPC -> SetBit(TH1::kNoStats);
        B_average_VS_Centrality_MDC     -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality_MDC -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality_MDC -> SetBit(TH1::kNoStats);
        B_average_VS_Centrality_FW      -> SetBit(TH1::kNoStats);
        Npart_average_VS_Centrality_FW  -> SetBit(TH1::kNoStats);
        Ncoll_average_VS_Centrality_FW  -> SetBit(TH1::kNoStats);

	B_average_VS_Centrality         -> SetLineColor(7);
	Npart_average_VS_Centrality     -> SetLineColor(7);
	Ncoll_average_VS_Centrality     -> SetLineColor(7);	
	B_average_VS_Centrality_TOF     -> SetLineColor(kBlack);
	Npart_average_VS_Centrality_TOF -> SetLineColor(kBlack);
	Ncoll_average_VS_Centrality_TOF -> SetLineColor(kBlack);
	B_average_VS_Centrality_RPC     -> SetLineColor(kRed+1);
	Npart_average_VS_Centrality_RPC -> SetLineColor(kRed+1);
	Ncoll_average_VS_Centrality_RPC -> SetLineColor(kRed+1);
	B_average_VS_Centrality_MDC     -> SetLineColor(kGreen+1);
	Npart_average_VS_Centrality_MDC -> SetLineColor(kGreen+1);
	Ncoll_average_VS_Centrality_MDC -> SetLineColor(kGreen+1);
	B_average_VS_Centrality_FW      -> SetLineColor(kBlue+1);
	Npart_average_VS_Centrality_FW  -> SetLineColor(kBlue+1);
	Ncoll_average_VS_Centrality_FW  -> SetLineColor(kBlue+1);

	B_average_VS_Centrality         -> SetLineWidth(1);
	Npart_average_VS_Centrality     -> SetLineWidth(1);
	Ncoll_average_VS_Centrality     -> SetLineWidth(1);	
	B_average_VS_Centrality_TOF     -> SetLineWidth(1);
	Npart_average_VS_Centrality_TOF -> SetLineWidth(1);
	Ncoll_average_VS_Centrality_TOF -> SetLineWidth(1);
	B_average_VS_Centrality_RPC     -> SetLineWidth(1);
	Npart_average_VS_Centrality_RPC -> SetLineWidth(1);
	Ncoll_average_VS_Centrality_RPC -> SetLineWidth(1);
	B_average_VS_Centrality_MDC     -> SetLineWidth(1);
	Npart_average_VS_Centrality_MDC -> SetLineWidth(1);
	Ncoll_average_VS_Centrality_MDC -> SetLineWidth(1);
	B_average_VS_Centrality_FW      -> SetLineWidth(1);
	Npart_average_VS_Centrality_FW  -> SetLineWidth(1);
	Ncoll_average_VS_Centrality_FW  -> SetLineWidth(1);

	B_average_VS_Centrality         -> SetMarkerStyle(20);
	Npart_average_VS_Centrality     -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality     -> SetMarkerStyle(20);	
	B_average_VS_Centrality_TOF     -> SetMarkerStyle(20);
	Npart_average_VS_Centrality_TOF -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality_TOF -> SetMarkerStyle(20);
	B_average_VS_Centrality_RPC     -> SetMarkerStyle(20);
	Npart_average_VS_Centrality_RPC -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality_RPC -> SetMarkerStyle(20);
	B_average_VS_Centrality_MDC     -> SetMarkerStyle(20);
	Npart_average_VS_Centrality_MDC -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality_MDC -> SetMarkerStyle(20);
	B_average_VS_Centrality_FW      -> SetMarkerStyle(20);
	Npart_average_VS_Centrality_FW  -> SetMarkerStyle(20);
	Ncoll_average_VS_Centrality_FW  -> SetMarkerStyle(20);

	B_average_VS_Centrality         -> SetMarkerSize(5);
	Npart_average_VS_Centrality     -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality     -> SetMarkerSize(5);	
	B_average_VS_Centrality_TOF     -> SetMarkerSize(5);
	Npart_average_VS_Centrality_TOF -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality_TOF -> SetMarkerSize(5);
	B_average_VS_Centrality_RPC     -> SetMarkerSize(5);
	Npart_average_VS_Centrality_RPC -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality_RPC -> SetMarkerSize(5);
	B_average_VS_Centrality_MDC     -> SetMarkerSize(5);
	Npart_average_VS_Centrality_MDC -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality_MDC -> SetMarkerSize(5);
	B_average_VS_Centrality_FW      -> SetMarkerSize(5);
	Npart_average_VS_Centrality_FW  -> SetMarkerSize(5);
	Ncoll_average_VS_Centrality_FW  -> SetMarkerSize(5);

	B_average_VS_Centrality         -> SetMarkerColor(7);
	Npart_average_VS_Centrality     -> SetMarkerColor(7);
	Ncoll_average_VS_Centrality     -> SetMarkerColor(7);	
	B_average_VS_Centrality_TOF     -> SetMarkerColor(kBlack);
	Npart_average_VS_Centrality_TOF -> SetMarkerColor(kBlack);
	Ncoll_average_VS_Centrality_TOF -> SetMarkerColor(kBlack);
	B_average_VS_Centrality_RPC     -> SetMarkerColor(kRed+1);
	Npart_average_VS_Centrality_RPC -> SetMarkerColor(kRed+1);
	Ncoll_average_VS_Centrality_RPC -> SetMarkerColor(kRed+1);
	B_average_VS_Centrality_MDC     -> SetMarkerColor(kGreen+1);
	Npart_average_VS_Centrality_MDC -> SetMarkerColor(kGreen+1);
	Ncoll_average_VS_Centrality_MDC -> SetMarkerColor(kGreen+1);
	B_average_VS_Centrality_FW      -> SetMarkerColor(kBlue+1);
	Npart_average_VS_Centrality_FW  -> SetMarkerColor(kBlue+1);
	Ncoll_average_VS_Centrality_FW  -> SetMarkerColor(kBlue+1);

	B_average_VS_Centrality         -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	B_average_VS_Centrality_TOF     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality_TOF -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality_TOF -> GetXaxis() -> SetNdivisions (10, kTRUE);
	B_average_VS_Centrality_RPC     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality_RPC -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality_RPC -> GetXaxis() -> SetNdivisions (10, kTRUE);
	B_average_VS_Centrality_MDC     -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality_MDC -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality_MDC -> GetXaxis() -> SetNdivisions (10, kTRUE);
	B_average_VS_Centrality_FW      -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Npart_average_VS_Centrality_FW  -> GetXaxis() -> SetNdivisions (10, kTRUE);
	Ncoll_average_VS_Centrality_FW  -> GetXaxis() -> SetNdivisions (10, kTRUE);

	B_VS_CentralityHisto_TOF[CentralityClasses]     = B_VS_Multiplicity_TOF->ProjectionY("B_VS_CentralityClass_TOF 0%-100%", 0, 97);
	Npart_VS_CentralityHisto_TOF[CentralityClasses] = Npart_VS_Multiplicity_TOF->ProjectionY("Npart_VS_CentralityClass_TOF 0%-100%", 0, 97);
	Ncoll_VS_CentralityHisto_TOF[CentralityClasses] = Ncoll_VS_Multiplicity_TOF->ProjectionY("Ncoll_VS_CentralityClass_TOF 0%-100%", 0, 97);
       	for (int i=0; i<entries_TOF; i++) {
		Borders_TOF -> GetEntry(i);
		B_VS_CentralityHisto_TOF[i]     = B_VS_Multiplicity_TOF->ProjectionY(Form("B_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_TOF, MaxBorder_TOF);
		Npart_VS_CentralityHisto_TOF[i] = Npart_VS_Multiplicity_TOF->ProjectionY(Form("Npart_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_TOF, MaxBorder_TOF);
		Ncoll_VS_CentralityHisto_TOF[i] = Ncoll_VS_Multiplicity_TOF->ProjectionY(Form("Ncoll_VS_CentralityClass_TOF %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_TOF, MaxBorder_TOF);
		}

	B_VS_CentralityHisto_RPC[CentralityClasses]     = B_VS_Multiplicity_RPC->ProjectionY("B_VS_CentralityClass_RPC 0%-100%", 0, 188);
	Npart_VS_CentralityHisto_RPC[CentralityClasses] = Npart_VS_Multiplicity_RPC->ProjectionY("Npart_VS_CentralityClass_RPC 0%-100%", 0, 188);
	Ncoll_VS_CentralityHisto_RPC[CentralityClasses] = Ncoll_VS_Multiplicity_RPC->ProjectionY("Ncoll_VS_CentralityClass_RPC 0%-100%", 0, 188);
       	for (int i=0; i<entries_RPC; i++) {
		Borders_RPC -> GetEntry(i);
		B_VS_CentralityHisto_RPC[i]     = B_VS_Multiplicity_RPC->ProjectionY(Form("B_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_RPC, MaxBorder_RPC);
		Npart_VS_CentralityHisto_RPC[i] = Npart_VS_Multiplicity_RPC->ProjectionY(Form("Npart_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_RPC, MaxBorder_RPC);
		Ncoll_VS_CentralityHisto_RPC[i] = Ncoll_VS_Multiplicity_RPC->ProjectionY(Form("Ncoll_VS_CentralityClass_RPC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_RPC, MaxBorder_RPC);
		}

	B_VS_CentralityHisto_MDC[CentralityClasses]     = B_VS_Multiplicity_MDC->ProjectionY("B_VS_CentralityClass_MDC 0%-100%", 0, 101);
	Npart_VS_CentralityHisto_MDC[CentralityClasses] = Npart_VS_Multiplicity_MDC->ProjectionY("Npart_VS_CentralityClass_MDC 0%-100%", 0, 101);
	Ncoll_VS_CentralityHisto_MDC[CentralityClasses] = Ncoll_VS_Multiplicity_MDC->ProjectionY("Ncoll_VS_CentralityClass_MDC 0%-100%", 0, 101);
       	for (int i=0; i<entries_MDC; i++) {
		Borders_MDC -> GetEntry(i);
		B_VS_CentralityHisto_MDC[i]     = B_VS_Multiplicity_MDC->ProjectionY(Form("B_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_MDC, MaxBorder_MDC);
		Npart_VS_CentralityHisto_MDC[i] = Npart_VS_Multiplicity_MDC->ProjectionY(Form("Npart_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_MDC, MaxBorder_MDC);
		Ncoll_VS_CentralityHisto_MDC[i] = Ncoll_VS_Multiplicity_MDC->ProjectionY(Form("Ncoll_VS_CentralityClass_MDC %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_MDC, MaxBorder_MDC);
		}
	
	B_VS_CentralityHisto_FW[CentralityClasses]     = B_VS_Multiplicity_FW->ProjectionY("B_VS_CentralityClass_FW 0%-100%", 0, 99);
	Npart_VS_CentralityHisto_FW[CentralityClasses] = Npart_VS_Multiplicity_FW->ProjectionY("Npart_VS_CentralityClass_FW 0%-100%", 0, 99);
	Ncoll_VS_CentralityHisto_FW[CentralityClasses] = Ncoll_VS_Multiplicity_FW->ProjectionY("Ncoll_VS_CentralityClass_FW 0%-100%", 0, 99);
       	for (int i=0; i<entries_FW; i++) {
		Borders_FW -> GetEntry(i);
		B_VS_CentralityHisto_FW[i]     = B_VS_Multiplicity_FW->ProjectionY(Form("B_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_FW, MaxBorder_FW);
		Npart_VS_CentralityHisto_FW[i] = Npart_VS_Multiplicity_FW->ProjectionY(Form("Npart_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_FW, MaxBorder_FW);
		Ncoll_VS_CentralityHisto_FW[i] = Ncoll_VS_Multiplicity_FW->ProjectionY(Form("Ncoll_VS_CentralityClass_FW %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses), MinBorder_FW, MaxBorder_FW);
		}

	int j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		B_VS_CentralityHisto_TOF[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) B_VS_CentralityHisto_TOF[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {B_VS_CentralityHisto_TOF[i] -> SetXTitle("B, fm"); B_VS_CentralityHisto_TOF[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Npart_VS_CentralityHisto_TOF[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Npart_VS_CentralityHisto_TOF[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Npart_VS_CentralityHisto_TOF[i] -> SetXTitle("N_{part}"); Npart_VS_CentralityHisto_TOF[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Ncoll_VS_CentralityHisto_TOF[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Ncoll_VS_CentralityHisto_TOF[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Ncoll_VS_CentralityHisto_TOF[i] -> SetXTitle("N_{coll}"); Ncoll_VS_CentralityHisto_TOF[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		B_VS_CentralityHisto_RPC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) B_VS_CentralityHisto_RPC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {B_VS_CentralityHisto_RPC[i] -> SetXTitle("B, fm"); B_VS_CentralityHisto_RPC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Npart_VS_CentralityHisto_RPC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Npart_VS_CentralityHisto_RPC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Npart_VS_CentralityHisto_RPC[i] -> SetXTitle("N_{part}"); Npart_VS_CentralityHisto_RPC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Ncoll_VS_CentralityHisto_RPC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Ncoll_VS_CentralityHisto_RPC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Ncoll_VS_CentralityHisto_RPC[i] -> SetXTitle("N_{coll}"); Ncoll_VS_CentralityHisto_RPC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		B_VS_CentralityHisto_MDC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) B_VS_CentralityHisto_MDC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {B_VS_CentralityHisto_MDC[i] -> SetXTitle("B, fm"); B_VS_CentralityHisto_MDC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Npart_VS_CentralityHisto_MDC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Npart_VS_CentralityHisto_MDC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Npart_VS_CentralityHisto_MDC[i] -> SetXTitle("N_{part}"); Npart_VS_CentralityHisto_MDC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Ncoll_VS_CentralityHisto_MDC[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Ncoll_VS_CentralityHisto_MDC[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Ncoll_VS_CentralityHisto_MDC[i] -> SetXTitle("N_{coll}"); Ncoll_VS_CentralityHisto_MDC[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		B_VS_CentralityHisto_FW[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) B_VS_CentralityHisto_FW[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {B_VS_CentralityHisto_FW[i] -> SetXTitle("B, fm"); B_VS_CentralityHisto_FW[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Npart_VS_CentralityHisto_FW[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Npart_VS_CentralityHisto_FW[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Npart_VS_CentralityHisto_FW[i] -> SetXTitle("N_{part}"); Npart_VS_CentralityHisto_FW[i] -> SetYTitle("counts");}

	j=1; 
	for (int i = 0; i < CentralityClasses+1; i++) {
		Ncoll_VS_CentralityHisto_FW[i] -> SetLineColor(j);
		j++;
		if (j==9) j=1;
		}
	for (int i = 0; i < CentralityClasses+1; i++) Ncoll_VS_CentralityHisto_FW[i] -> SetLineWidth(2);
	for (int i = 0; i < CentralityClasses+1; i++) {Ncoll_VS_CentralityHisto_FW[i] -> SetXTitle("N_{coll}"); Ncoll_VS_CentralityHisto_FW[i] -> SetYTitle("counts");}
	
	for (int i = 0; i < CentralityClasses; i++) {
		cout<<i<<endl;
		Ncc=i+1;
		MinPercent=(i)*100/CentralityClasses;
		MaxPercent=(i+1)*100/CentralityClasses;
		
		Borders_TOF -> GetEntry(i);
		Borders_RPC -> GetEntry(i);
		Borders_MDC -> GetEntry(i);
		Borders_FW  -> GetEntry(i);

		MinBorder_TOF_R=MinBorder_TOF;
		MaxBorder_TOF_R=MaxBorder_TOF;
		MinBorder_RPC_R=MinBorder_RPC;
		MaxBorder_RPC_R=MaxBorder_RPC;
		MinBorder_MDC_R=MinBorder_MDC;
		MaxBorder_MDC_R=MaxBorder_MDC;
		MinBorder_FW_R=MinBorder_FW;
		MaxBorder_FW_R=MaxBorder_FW;

		B_TOF_av=B_VS_CentralityHisto_TOF[i]->GetMean();
		Npart_TOF_av=Npart_VS_CentralityHisto_TOF[i]->GetMean();
		Ncoll_TOF_av=Ncoll_VS_CentralityHisto_TOF[i]->GetMean();
		B_RPC_av=B_VS_CentralityHisto_RPC[i]->GetMean();
		Npart_RPC_av=Npart_VS_CentralityHisto_RPC[i]->GetMean();
		Ncoll_RPC_av=Ncoll_VS_CentralityHisto_RPC[i]->GetMean();
		B_MDC_av=B_VS_CentralityHisto_MDC[i]->GetMean();
		Npart_MDC_av=Npart_VS_CentralityHisto_MDC[i]->GetMean();
		Ncoll_MDC_av=Ncoll_VS_CentralityHisto_MDC[i]->GetMean();
		B_FW_av=B_VS_CentralityHisto_FW[i]->GetMean();
		Npart_FW_av=Npart_VS_CentralityHisto_FW[i]->GetMean();
		Ncoll_FW_av=Ncoll_VS_CentralityHisto_FW[i]->GetMean();
		B_av=(B_TOF_av+B_RPC_av+B_MDC_av+B_FW_av)/4.0;
		Npart_av=(Npart_TOF_av+Npart_RPC_av+Npart_MDC_av+Npart_FW_av)/4.0;
		Ncoll_av=(Ncoll_TOF_av+Ncoll_RPC_av+Ncoll_MDC_av+Ncoll_FW_av)/4.0;

		RMS_B_TOF_av=B_VS_CentralityHisto_TOF[i]->GetRMS();
		RMS_Npart_TOF_av=Npart_VS_CentralityHisto_TOF[i]->GetRMS();
		RMS_Ncoll_TOF_av=Ncoll_VS_CentralityHisto_TOF[i]->GetRMS();
		RMS_B_RPC_av=B_VS_CentralityHisto_RPC[i]->GetRMS();
		RMS_Npart_RPC_av=Npart_VS_CentralityHisto_RPC[i]->GetRMS();
		RMS_Ncoll_RPC_av=Ncoll_VS_CentralityHisto_RPC[i]->GetRMS();
		RMS_B_MDC_av=B_VS_CentralityHisto_MDC[i]->GetRMS();
		RMS_Npart_MDC_av=Npart_VS_CentralityHisto_MDC[i]->GetRMS();
		RMS_Ncoll_MDC_av=Ncoll_VS_CentralityHisto_MDC[i]->GetRMS();
		RMS_B_FW_av=B_VS_CentralityHisto_FW[i]->GetRMS();
		RMS_Npart_FW_av=Npart_VS_CentralityHisto_FW[i]->GetRMS();
		RMS_Ncoll_FW_av=Ncoll_VS_CentralityHisto_FW[i]->GetRMS();
		RMS_B_av=(TMath::Power((TMath::Power(RMS_B_TOF_av,2)+TMath::Power(RMS_B_RPC_av,2)+TMath::Power(RMS_B_MDC_av,2)+TMath::Power(RMS_B_FW_av,2)),0.5))/4.0;
		RMS_B_av=(TMath::Power((TMath::Power(RMS_B_TOF_av,2)+TMath::Power(RMS_B_RPC_av,2)+TMath::Power(RMS_B_MDC_av,2)),0.5))/3.0;
		RMS_Npart_av=(TMath::Power((TMath::Power(RMS_Npart_TOF_av,2)+TMath::Power(RMS_Npart_RPC_av,2)+TMath::Power(RMS_Npart_MDC_av,2)+TMath::Power(RMS_Npart_FW_av,2)),0.5))/4.0;
		RMS_Npart_av=(TMath::Power((TMath::Power(RMS_Npart_TOF_av,2)+TMath::Power(RMS_Npart_RPC_av,2)+TMath::Power(RMS_Npart_MDC_av,2)),0.5))/3.0;
		RMS_Ncoll_av=(TMath::Power((TMath::Power(RMS_Ncoll_TOF_av,2)+TMath::Power(RMS_Ncoll_RPC_av,2)+TMath::Power(RMS_Ncoll_MDC_av,2)+TMath::Power(RMS_Ncoll_FW_av,2)),0.5))/4.0;
		RMS_Ncoll_av=(TMath::Power((TMath::Power(RMS_Ncoll_TOF_av,2)+TMath::Power(RMS_Ncoll_RPC_av,2)+TMath::Power(RMS_Ncoll_MDC_av,2)),0.5))/3.0;

		B_average_VS_Centrality         -> SetBinContent(i+1,B_av);
		Npart_average_VS_Centrality     -> SetBinContent(i+1,Npart_av);
		Ncoll_average_VS_Centrality     -> SetBinContent(i+1,Ncoll_av);	
		B_average_VS_Centrality_TOF     -> SetBinContent(i+1,B_TOF_av);
		Npart_average_VS_Centrality_TOF -> SetBinContent(i+1,Npart_TOF_av);
		Ncoll_average_VS_Centrality_TOF -> SetBinContent(i+1,Ncoll_TOF_av);
		B_average_VS_Centrality_RPC     -> SetBinContent(i+1,B_RPC_av);
		Npart_average_VS_Centrality_RPC -> SetBinContent(i+1,Npart_RPC_av);
		Ncoll_average_VS_Centrality_RPC -> SetBinContent(i+1,Ncoll_RPC_av);
		B_average_VS_Centrality_MDC     -> SetBinContent(i+1,B_MDC_av);
		Npart_average_VS_Centrality_MDC -> SetBinContent(i+1,Npart_MDC_av);
		Ncoll_average_VS_Centrality_MDC -> SetBinContent(i+1,Ncoll_MDC_av);
		B_average_VS_Centrality_FW      -> SetBinContent(i+1,B_FW_av);
		Npart_average_VS_Centrality_FW  -> SetBinContent(i+1,Npart_FW_av);
		Ncoll_average_VS_Centrality_FW  -> SetBinContent(i+1,Ncoll_FW_av);
	
		B_average_VS_Centrality         -> SetBinError(i+1,RMS_B_av);
		Npart_average_VS_Centrality     -> SetBinError(i+1,RMS_Npart_av);
		Ncoll_average_VS_Centrality     -> SetBinError(i+1,RMS_Ncoll_av);	
		B_average_VS_Centrality_TOF     -> SetBinError(i+1,RMS_B_TOF_av);
		Npart_average_VS_Centrality_TOF -> SetBinError(i+1,RMS_Npart_TOF_av);
		Ncoll_average_VS_Centrality_TOF -> SetBinError(i+1,RMS_Ncoll_TOF_av);
		B_average_VS_Centrality_RPC     -> SetBinError(i+1,RMS_B_RPC_av);
		Npart_average_VS_Centrality_RPC -> SetBinError(i+1,RMS_Npart_RPC_av);
		Ncoll_average_VS_Centrality_RPC -> SetBinError(i+1,RMS_Ncoll_RPC_av);
		B_average_VS_Centrality_MDC     -> SetBinError(i+1,RMS_B_MDC_av);
		Npart_average_VS_Centrality_MDC -> SetBinError(i+1,RMS_Npart_MDC_av);
		Ncoll_average_VS_Centrality_MDC -> SetBinError(i+1,RMS_Ncoll_MDC_av);
		B_average_VS_Centrality_FW      -> SetBinError(i+1,RMS_B_FW_av);
		Npart_average_VS_Centrality_FW  -> SetBinError(i+1,RMS_Npart_FW_av);
		Ncoll_average_VS_Centrality_FW  -> SetBinError(i+1,RMS_Ncoll_FW_av);

		Result->Fill();
		}

	TLatex latex;

	TCanvas* c1 = new TCanvas("B_VS_Centrality_TOF","B_VS_Centrality_TOF", 1500, 900);
	TLegend legend1(0.65,0.65,1.0,1.0, "B VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend1.AddEntry(B_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend1.AddEntry(B_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_TOF[i]->Draw("same");
	legend1.Draw("same");
	c1->Write();
	for (int i = 0; i <= CentralityClasses; i++) B_VS_CentralityHisto_TOF[i] -> Write();
	c1->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_TOF.pdf");
	c1->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_TOF.C");

	TCanvas* c2 = new TCanvas("Npart_VS_Centrality_TOF","Npart_VS_Centrality_TOF", 1500, 900);
	c2->SetLogy();
	TLegend legend2(0.65,0.65,1.0,1.0, "N_{part} VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend2.AddEntry(Npart_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend2.AddEntry(Npart_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_TOF[i]->Draw("same");
	legend2.Draw("same");
	c2->Write();
	for (int i = 0; i <= CentralityClasses; i++) Npart_VS_CentralityHisto_TOF[i] -> Write();
	c2->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_TOF.pdf");
	c2->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_TOF.C");

	TCanvas* c3 = new TCanvas("Ncoll_VS_Centrality_TOF","Ncoll_VS_Centrality_TOF", 1500, 900);
	c3->SetLogy();
	TLegend legend3(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend3.AddEntry(Ncoll_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend3.AddEntry(Ncoll_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_TOF[i]->Draw("same");
	legend3.Draw("same");
	c3->Write();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_TOF[i] -> Write();
	c3->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_TOF.pdf");
	c3->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_TOF.C");	

	TCanvas* c4 = new TCanvas("B_VS_Centrality_RPC","B_VS_Centrality_RPC", 1500, 900);
	TLegend legend4(0.65,0.65,1.0,1.0, "B VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend4.AddEntry(B_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend4.AddEntry(B_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_RPC[i]->Draw("same");
	legend4.Draw("same");
	c4->Write();
	for (int i = 0; i <= CentralityClasses; i++) B_VS_CentralityHisto_RPC[i] -> Write();
	c4->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_RPC.pdf");
	c4->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_RPC.C");

	TCanvas* c5 = new TCanvas("Npart_VS_Centrality_RPC","Npart_VS_Centrality_RPC", 1500, 900);
	c5->SetLogy();
	TLegend legend5(0.65,0.65,1.0,1.0, "N_{part} VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend5.AddEntry(Npart_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend5.AddEntry(Npart_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_RPC[i]->Draw("same");
	legend5.Draw("same");
	c5->Write();
	for (int i = 0; i <= CentralityClasses; i++) Npart_VS_CentralityHisto_RPC[i] -> Write();
	c5->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_RPC.pdf");
	c5->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_RPC.C");

	TCanvas* c6 = new TCanvas("Ncoll_VS_Centrality_RPC","Ncoll_VS_Centrality_RPC", 1500, 900);
	c6->SetLogy();
	TLegend legend6(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend6.AddEntry(Ncoll_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend6.AddEntry(Ncoll_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_RPC[i]->Draw("same");
	legend6.Draw("same");
	c6->Write();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_RPC[i] -> Write();
	c6->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_RPC.pdf");
	c6->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_RPC.C");

	TCanvas* c7 = new TCanvas("B_VS_Centrality_MDC","B_VS_Centrality_MDC", 1500, 900);
	TLegend legend7(0.65,0.65,1.0,1.0, "B VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend7.AddEntry(B_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend7.AddEntry(B_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_MDC[i]->Draw("same");
	legend7.Draw("same");
	c7->Write();
	for (int i = 0; i <= CentralityClasses; i++) B_VS_CentralityHisto_MDC[i] -> Write();
	c7->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_MDC.pdf");
	c7->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_MDC.C");

	TCanvas* c8 = new TCanvas("Npart_VS_Centrality_MDC","Npart_VS_Centrality_MDC", 1500, 900);
	c8->SetLogy();
	TLegend legend8(0.65,0.65,1.0,1.0, "N_{part} VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend8.AddEntry(Npart_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend8.AddEntry(Npart_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_MDC[i]->Draw("same");
	legend8.Draw("same");
	c8->Write();
	for (int i = 0; i <= CentralityClasses; i++) Npart_VS_CentralityHisto_MDC[i] -> Write();
	c8->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_MDC.pdf");
	c8->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_MDC.C");

	TCanvas* c9 = new TCanvas("Ncoll_VS_Centrality_MDC","Ncoll_VS_Centrality_MDC", 1500, 900);
	c9->SetLogy();
	TLegend legend9(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend9.AddEntry(Ncoll_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend9.AddEntry(Ncoll_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_MDC[i]->Draw("same");
	legend9.Draw("same");
	c9->Write();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_MDC[i] -> Write();
	c9->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_MDC.pdf");
	c9->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_MDC.C");

	TCanvas* c10 = new TCanvas("B_VS_Centrality_FW","B_VS_Centrality_FW", 1500, 900);
	TLegend legend10(0.65,0.65,1.0,1.0, "B VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend10.AddEntry(B_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend10.AddEntry(B_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_FW[i]->Draw("same");
	legend10.Draw("same");
	c10->Write();
	for (int i = 0; i <= CentralityClasses; i++) B_VS_CentralityHisto_FW[i] -> Write();
	c10->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_FW.pdf");
	c10->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_FW.C");

	TCanvas* c11 = new TCanvas("Npart_VS_Centrality_FW","Npart_VS_Centrality_FW", 1500, 900);
	c11->SetLogy();
	TLegend legend11(0.65,0.65,1.0,1.0, "N_{part} VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend11.AddEntry(Npart_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend11.AddEntry(Npart_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_FW[i]->Draw("same");
	legend11.Draw("same");
	c11->Write();
	for (int i = 0; i <= CentralityClasses; i++) Npart_VS_CentralityHisto_FW[i] -> Write();
	c11->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_FW.pdf");
	c11->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_FW.C");

	TCanvas* c12 = new TCanvas("Ncoll_VS_Centrality_FW","Ncoll_VS_Centrality_FW", 1500, 900);
	c12->SetLogy();
	TLegend legend12(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend12.AddEntry(Ncoll_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend12.AddEntry(Ncoll_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_FW[i]->Draw("same");
	legend12.Draw("same");
	c12->Write();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_FW[i] -> Write();
	c12->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_FW.pdf");
	c12->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_FW.C");

	TCanvas* c13 = new TCanvas("B_average_VS_Centrality","B_average_VS_Centrality", 1500, 900);
	TLegend legend13(0.65,0.65,1.0,1.0, "<B> VS Centrality");
	legend13.AddEntry(B_average_VS_Centrality_TOF, "TOF");
	legend13.AddEntry(B_average_VS_Centrality_RPC, "RPC");
	legend13.AddEntry(B_average_VS_Centrality_MDC, "MDC");
	legend13.AddEntry(B_average_VS_Centrality_FW, "FW");
	B_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	B_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	B_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	B_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend13.Draw("same");
	c13->Write();
	c13->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_Result.pdf");
	c13->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality_Result.C");

	TCanvas* c14 = new TCanvas("Npart_average_VS_Centrality","Npart_average_VS_Centrality", 1500, 900);
	TLegend legend14(0.65,0.65,1.0,1.0, "<N_{part}> VS Centrality");
	legend14.AddEntry(Npart_average_VS_Centrality_TOF, "TOF");
	legend14.AddEntry(Npart_average_VS_Centrality_RPC, "RPC");
	legend14.AddEntry(Npart_average_VS_Centrality_MDC, "MDC");
	legend14.AddEntry(Npart_average_VS_Centrality_FW, "FW");
	Npart_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	Npart_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	Npart_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	Npart_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend14.Draw("same");
	c14->Write();
	c14->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_Result.pdf");
	c14->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality_Result.C");

	TCanvas* c15 = new TCanvas("Ncoll_average_VS_Centrality","Ncoll_average_VS_Centrality", 1500, 900);
	TLegend legend15(0.65,0.65,1.0,1.0, "<N_{coll}> VS Centrality");
	legend15.AddEntry(Ncoll_average_VS_Centrality_TOF, "TOF");
	legend15.AddEntry(Ncoll_average_VS_Centrality_RPC, "RPC");
	legend15.AddEntry(Ncoll_average_VS_Centrality_MDC, "MDC");
	legend15.AddEntry(Ncoll_average_VS_Centrality_FW, "FW");
	Ncoll_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	Ncoll_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	Ncoll_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	Ncoll_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend15.Draw("same");
	c15->Write();
	c15->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_Result.pdf");
	c15->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality_Result.C");
	
	TCanvas* c16 = new TCanvas("B_VS_Centrality","B_VS_Centrality", 3000, 1800);
	c16->Divide(2,2);
	c16->cd(1);
	TLegend legend161(0.65,0.65,1.0,1.0, "B VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend161.AddEntry(B_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend161.AddEntry(B_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_TOF[i]->Draw("same");
	legend161.Draw("same");
	c16->cd(2);
	TLegend legend164(0.65,0.65,1.0,1.0, "B VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend164.AddEntry(B_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend164.AddEntry(B_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_RPC[i]->Draw("same");
	legend164.Draw("same");
	c16->cd(3);
	TLegend legend167(0.65,0.65,1.0,1.0, "B VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend167.AddEntry(B_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend167.AddEntry(B_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_MDC[i]->Draw("same");
	legend167.Draw("same");
	c16->cd(4);
	TLegend legend1610(0.65,0.65,1.0,1.0, "B VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend1610.AddEntry(B_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend1610.AddEntry(B_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	B_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) B_VS_CentralityHisto_FW[i]->Draw("same");
	legend1610.Draw("same");
	c16->cd();
	latex.DrawLatex(0.5, 0.5, "HADES Au-Au@1.23AGeV");
	c16->Write();
	c16->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality.pdf");
	c16->SaveAs("/home/vad/NIR_codes/Centrality/Send/B_VS_Centrality.C");

	std::unique_ptr <TCanvas> c17 {new TCanvas("Npart_VS_Centrality","N_{part} VS Centrality", 3000, 1800)};
	c17->Divide(2,2);
	c17->cd(1);
	gPad->SetLogy();
	TLegend legend172(0.65,0.65,1.0,1.0, "N_{part} VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend172.AddEntry(Npart_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend172.AddEntry(Npart_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_TOF[i]->Draw("same");
	legend172.Draw("same");
	c17->cd(2);
	gPad->SetLogy();
	TLegend legend175(0.65,0.65,1.0,1.0, "N_{part} VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend175.AddEntry(Npart_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend175.AddEntry(Npart_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_RPC[i]->Draw("same");
	legend175.Draw("same");
	c17->cd(3);
	gPad->SetLogy();
	TLegend legend178(0.65,0.65,1.0,1.0, "N_{part} VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend178.AddEntry(Npart_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend178.AddEntry(Npart_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_MDC[i]->Draw("same");
	legend178.Draw("same");
	c17->cd(4);
	gPad->SetLogy();
	TLegend legend1711(0.65,0.65,1.0,1.0, "N_{part} VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend1711.AddEntry(Npart_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend1711.AddEntry(Npart_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	Npart_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i < CentralityClasses; i++) Npart_VS_CentralityHisto_FW[i]->Draw("same");
	legend1711.Draw("same");
	c17->cd();
	latex.DrawLatex(0.5, 0.5, "HADES Au-Au@1.23AGeV");
	c17->Write();
	c17->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality.pdf");
	c17->SaveAs("/home/vad/NIR_codes/Centrality/Send/Npart_VS_Centrality.C");

	std::unique_ptr <TCanvas> c18 {new TCanvas("Ncoll_VS_Centrality","N_{coll}_VS_Centrality", 3000, 1800)};
	c18->Divide(2,2);
	c18->cd(1);
	gPad->SetLogy();
	TLegend legend183(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality TOF");
	for (int i = 0; i < CentralityClasses; i++) legend183.AddEntry(Ncoll_VS_CentralityHisto_TOF[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend183.AddEntry(Ncoll_VS_CentralityHisto_TOF[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_TOF[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_TOF[i]->Draw("same");
	legend183.Draw("same");
	c18->cd(2);
	gPad->SetLogy();
	TLegend legend186(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality RPC");
	for (int i = 0; i < CentralityClasses; i++) legend186.AddEntry(Ncoll_VS_CentralityHisto_RPC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend6.AddEntry(Ncoll_VS_CentralityHisto_RPC[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_RPC[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_RPC[i]->Draw("same");
	legend186.Draw("same");;
	c18->cd(3);
	gPad->SetLogy();
	TLegend legend189(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality MDC");
	for (int i = 0; i < CentralityClasses; i++) legend189.AddEntry(Ncoll_VS_CentralityHisto_MDC[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend9.AddEntry(Ncoll_VS_CentralityHisto_MDC[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_MDC[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_MDC[i]->Draw("same");
	legend189.Draw("same");
	c18->cd(4);
	gPad->SetLogy();
	TLegend legend1812(0.65,0.65,1.0,1.0, "N_{coll} VS Centrality FW");
	for (int i = 0; i < CentralityClasses; i++) legend1812.AddEntry(Ncoll_VS_CentralityHisto_FW[i], Form("CentralityClass %.1f%%-%.1f%%", i*100.0/CentralityClasses, (i+1)*100.0/CentralityClasses));
	legend1812.AddEntry(Ncoll_VS_CentralityHisto_FW[CentralityClasses], "CentralityClass 0%-100%");
	Ncoll_VS_CentralityHisto_FW[CentralityClasses]->Draw();
	for (int i = 0; i <= CentralityClasses; i++) Ncoll_VS_CentralityHisto_FW[i]->Draw("same");
	legend1812.Draw("same");
	c18->cd();
	latex.DrawLatex(0.5, 0.5, "HADES Au-Au@1.23AGeV");
	c18->Write();
	c18->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality.pdf");
	c18->SaveAs("/home/vad/NIR_codes/Centrality/Send/Ncoll_VS_Centrality.C");

	TCanvas* c19 = new TCanvas("Result","", 9000, 2000);
	c19->Divide(3,1);
	c19->cd(1);
	TLegend legend1913(0.1,0.75,0.35,1.0, "<B> VS Centrality");
	legend1913.AddEntry(B_average_VS_Centrality_TOF, "TOF");
	legend1913.AddEntry(B_average_VS_Centrality_RPC, "RPC");
	legend1913.AddEntry(B_average_VS_Centrality_MDC, "MDC");
	legend1913.AddEntry(B_average_VS_Centrality_FW, "FW");
	B_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	B_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	B_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	B_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend1913.Draw("same");
	c19->cd(2);
	TLegend legend1914(0.75,0.75,1.0,1.0, "<N_{part}> VS Centrality");
	legend1914.AddEntry(Npart_average_VS_Centrality_TOF, "TOF");
	legend1914.AddEntry(Npart_average_VS_Centrality_RPC, "RPC");
	legend1914.AddEntry(Npart_average_VS_Centrality_MDC, "MDC");
	legend1914.AddEntry(Npart_average_VS_Centrality_FW, "FW");
	Npart_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	Npart_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	Npart_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	Npart_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend1914.Draw("same");
	c19->cd(3);
	TLegend legend1915(0.75,0.75,1.0,1.0, "<N_{coll}> VS Centrality");
	legend1915.AddEntry(Ncoll_average_VS_Centrality_TOF, "TOF");
	legend1915.AddEntry(Ncoll_average_VS_Centrality_RPC, "RPC");
	legend1915.AddEntry(Ncoll_average_VS_Centrality_MDC, "MDC");
	legend1915.AddEntry(Ncoll_average_VS_Centrality_FW, "FW");
	Ncoll_average_VS_Centrality_TOF -> Draw("E1, P, X0");
	Ncoll_average_VS_Centrality_RPC -> Draw("same, E1, P, X0");
	Ncoll_average_VS_Centrality_MDC -> Draw("same, E1, P, X0");
	Ncoll_average_VS_Centrality_FW  -> Draw("same, E1, P, X0");
	legend1915.Draw("same");
	c19->cd();
	latex.DrawLatex(0.3, 0.95, "HADES Au-Au@1.23AGeV");
	c19->Write();
	c19->SaveAs("/home/vad/NIR_codes/Centrality/Send/Result.pdf");
	c19->SaveAs("/home/vad/NIR_codes/Centrality/Send/Result.C");

	B_average_VS_Centrality         -> Write();
	Npart_average_VS_Centrality     -> Write();
	Ncoll_average_VS_Centrality     -> Write();	
	B_average_VS_Centrality_TOF     -> Write();
	Npart_average_VS_Centrality_TOF -> Write();
	Ncoll_average_VS_Centrality_TOF -> Write();
	B_average_VS_Centrality_RPC     -> Write();
	Npart_average_VS_Centrality_RPC -> Write();
	Ncoll_average_VS_Centrality_RPC -> Write();
	B_average_VS_Centrality_MDC     -> Write();
	Npart_average_VS_Centrality_MDC -> Write();
	Ncoll_average_VS_Centrality_MDC -> Write();
	B_average_VS_Centrality_FW      -> Write();
	Npart_average_VS_Centrality_FW  -> Write();
	Ncoll_average_VS_Centrality_FW  -> Write();
	
	Result->Write();

	fOut->Close();
}
