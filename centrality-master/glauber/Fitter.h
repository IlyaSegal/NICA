/** @file   Fitter.h
    @class  Glauber::Fitter
    @author Viktor Klochkov (klochkov44@gmail.com)
    @author Ilya Selyuzhenkov (ilya.selyuzhenkov@gmail.com)
    @brief  Class to fit histo with Glauber based function
*/
#ifndef GlauberFitter_H
#define GlauberFitter_H 1

#include <vector>
#include <map>
#include <TH3F.h>
#include "TString.h"
#include "TNamed.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
// #include "TMinuit.h"


namespace Glauber
{
	enum eGlauberParameters {
		kNpart = 0, kNcoll, kNhard, kB, kBNN, kNcollpp, kNcollpn, kNcollnn, kVarX, kVarY, kVarXY, kNpartA, kNpartB, kNpart0, kAreaW, kPsi1, kEcc1, kPsi2, kEcc2, kPsi3, kEcc3, kPsi4, kEcc4, kPsi5, kEcc5, kAreaO, kAreaA, kX0, kY0, kPhi0, kLength, kMeanX, kMeanY, kMeanX2, kMeanY2, kMeanXY, kMeanXSystem, kMeanYSystem, kMeanXA, kMeanYA, kMeanXB, kMeanYB, kPhiA, kThetaA, kPhiB, kThetaB, kGP
    };

	const struct TGlauberParameters {
	  Int_t id;
	  TString name;
	  TString title; 
	  TString axis_title;
	  Float_t bin_value;
	  } gGlauberParameters[kGP] = {
	  	{ .id = kNpart,       .name = "Npart",       .title = "Number of participating nucleons",                .axis_title="N_{part}",               .bin_value = 1    },
	  	{ .id = kNcoll,       .name = "Ncoll",       .title = "Number of binary collisions",                     .axis_title="N_{coll}",               .bin_value = 1    },
	  	{ .id = kNhard,       .name = "Nhard",       .title = "Number of hard collisions",                       .axis_title="N_{hard}",               .bin_value = 1    },
		{ .id = kB,           .name = "B",           .title = "Impact parameter",                                .axis_title="#it{B}, fm",             .bin_value = 0.01 },
		{ .id = kBNN,         .name = "BNN",         .title = "Mean nucleon–nucleon impact parameter",           .axis_title="#it{B_{NN}}, fm",        .bin_value = 0.01 },
		{ .id = kNcollpp,     .name = "Ncollpp",     .title = "Number of pp collisions",                         .axis_title="N^{pp}_{coll}",          .bin_value = 1    },
		{ .id = kNcollpn,     .name = "Ncollpn",     .title = "Number of pn collisions",                         .axis_title="N^{pn}_{coll}",          .bin_value = 1    },
		{ .id = kNcollnn,     .name = "Ncollnn",     .title = "Number of nn collisions",                         .axis_title="N^{nn}_{coll}",          .bin_value = 1    },
		{ .id = kVarX,        .name = "VarX",        .title = "Variance of x for wounded nucleons",              .axis_title="#sigma^{2}_{x}, fm^{2}", .bin_value = 0.01 },
		{ .id = kVarY,        .name = "VarY",        .title = "Variance of y for wounded nucleons",              .axis_title="#sigma^{2}_{x}, fm^{2}", .bin_value = 0.01 },
		{ .id = kVarXY,       .name = "VarXY",       .title = "Covariance of x and y for wounded nucleons",      .axis_title="sigma_{xy}, fm^{2}",     .bin_value = 0.01 },
		{ .id = kNpartA,      .name = "NpartA",      .title = "Number of participating nucleons from nucleus A", .axis_title="N^{A}_{part}",           .bin_value = 1    },
		{ .id = kNpartB,      .name = "NpartB",      .title = "Number of participating nucleons from nucleus B", .axis_title="N^{B}_{part}",           .bin_value = 1    },
		{ .id = kNpart0,      .name = "Npart0",      .title = "Number of singly-wounded participating nucleons", .axis_title="N^{0}_{part}",           .bin_value = 1    },
		{ .id = kAreaW,       .name = "AreaW",       .title = "Area defined by width of participants",           .axis_title="AreaW, fm^{2}",          .bin_value = 0.01 },
		{ .id = kPsi1,        .name = "Psi1",        .title = "Event plane angle of 1st harmonic",               .axis_title="#psi_{1}, rad",          .bin_value = 0.01 },
		{ .id = kEcc1,        .name = "Ecc1",        .title = "Participant eccentricity for 1st harmonic",       .axis_title="#epsilon_{1}",           .bin_value = 0.01 },
		{ .id = kPsi2,        .name = "Psi2",        .title = "Event plane angle of 2nd harmonic",               .axis_title="#psi_{2}, rad",          .bin_value = 0.01 },
		{ .id = kEcc2,        .name = "Ecc2",        .title = "Participant eccentricity for 2nd harmonic",       .axis_title="#epsilon_{2}",           .bin_value = 0.01 },
		{ .id = kPsi3,        .name = "Psi3",        .title = "Event plane angle of 3rd harmonic",               .axis_title="#psi_{3}, rad",          .bin_value = 0.01 },
		{ .id = kEcc3,        .name = "Ecc3",        .title = "Participant eccentricity for 3rd harmonic",       .axis_title="#epsilon_{3}",           .bin_value = 0.01 },
		{ .id = kPsi4,        .name = "Psi4",        .title = "Event plane angle of 4th harmonic",               .axis_title="#psi_{4}, rad",          .bin_value = 0.01 },
		{ .id = kEcc4,        .name = "Ecc4",        .title = "Participant eccentricity for 4th harmonic",       .axis_title="#epsilon_{4}",           .bin_value = 0.01 },
		{ .id = kPsi5,        .name = "Psi5",        .title = "Event plane angle of 5th harmonic",               .axis_title="#psi_{5}, rad",          .bin_value = 0.01 },
		{ .id = kEcc5,        .name = "Ecc5",        .title = "Participant eccentricity for 5th harmonic",       .axis_title="#epsilon_{5}",           .bin_value = 0.01 },
		{ .id = kAreaO,       .name = "AreaO",       .title = "Area by ”or” of participants in grid",            .axis_title="Area OR",                .bin_value = 0.01 },
		{ .id = kAreaA,       .name = "AreaA",       .title = "Area by ”and” of participants in grid",           .axis_title="Area AND",               .bin_value = 0.01 },
		{ .id = kX0,          .name = "X0",          .title = "Production point in x",                           .axis_title="x, fm",                  .bin_value = 0.01 },
		{ .id = kY0,          .name = "Y0",          .title = "Production point in y",                           .axis_title="y, fm",                  .bin_value = 0.01 },
		{ .id = kPhi0,        .name = "Phi0",        .title = "Direction in #varphi",                            .axis_title="#varphi, rad",           .bin_value = 0.01 },
		{ .id = kLength,      .name = "Length",      .title = "Length in #varphi",                               .axis_title="p_{T} (GeV/#it{c})",     .bin_value = 0.01 },
		{ .id = kMeanX,       .name = "MeanX",       .title = "Mean of x for wounded nucleons",                  .axis_title="<x>, fm",                .bin_value = 0.01 },
		{ .id = kMeanY,       .name = "MeanY",       .title = "Mean of y for wounded nucleons",                  .axis_title="<y>, fm",                .bin_value = 0.01 },
		{ .id = kMeanX2,      .name = "MeanX2",      .title = "Mean of x^{2} for wounded nucleons",              .axis_title="<x^{2}>, fm^2",          .bin_value = 0.01 },
		{ .id = kMeanXY,      .name = "MeanY2",      .title = "Mean of y^{2} for wounded nucleons",              .axis_title="<y^{2}>, fm^2",          .bin_value = 0.01 },  
		{ .id = kMeanY2,      .name = "MeanXY",      .title = "Mean of xy for wounded nucleons",                 .axis_title="<xy>, fm^2",             .bin_value = 0.01 },
		{ .id = kMeanXSystem, .name = "MeanXSystem", .title = "Mean of x for all nucleons",                      .axis_title="<x>, fm",                .bin_value = 0.01 },
		{ .id = kMeanYSystem, .name = "MeanYSystem", .title = "Mean of y for all nucleons",                      .axis_title="<y>, fm",                .bin_value = 0.01 },
		{ .id = kMeanXA,      .name = "MeanXA",      .title = "Mean of x for nucleons in nucleus A",             .axis_title="<x>, fm",                .bin_value = 0.01 },
		{ .id = kMeanYA,      .name = "MeanYA",      .title = "Mean of y for nucleons in nucleus A",             .axis_title="<y>, fm",                .bin_value = 0.01 },
		{ .id = kMeanXB,      .name = "MeanXB",      .title = "Mean of x for nucleons in nucleus B",             .axis_title="<x>, fm",                .bin_value = 0.01 },
		{ .id = kMeanYB,      .name = "MeanYB",      .title = "Mean of y for nucleons in nucleus B",             .axis_title="<y>, fm",                .bin_value = 0.01 },
		{ .id = kPhiA,        .name = "PhiA",        .title = "Azimuthal angle for nucleus A",                   .axis_title="#varphi^{A}, rad",       .bin_value = 0.01 },
		{ .id = kThetaA,      .name = "ThetaA",      .title = "Polar angle for nucleus A",                       .axis_title="#theta^{A}, rad",        .bin_value = 0.01 },
		{ .id = kPhiB,        .name = "PhiB",        .title = "Azimuthal angle for nucleus B",                   .axis_title="#varphi^{B}, rad",       .bin_value = 0.01 },
		{ .id = kThetaB,      .name = "ThetaB",      .title = "Polar angle for nucleus B",                       .axis_title="#theta^{A}, rad",        .bin_value = 0.01 }
      };

    class Fitter
    {
        
    public:

    /**   Default constructor   **/
    Fitter() {};
    /**   Destructor   **/
    virtual ~Fitter(){};
        
    void Init(std::unique_ptr<TTree> tree);															                                                                // Initialize all parameters of class Fitter
    void SetGlauberFitHisto (Float_t f, Float_t mu, Float_t k, Bool_t Norm2Data = true);									                                        // Setting of model histogtam
    void NormalizeGlauberFit ();																                                                                    // Function for normilize model histogram with data histogram

    float FitGlauber (float *par);										                                                                                            // Main function for fitting
    void FindMuGoldenSection (TTree *tree, float *mu, float *chi2, float *chi2_error, int *n, float *sigma, float mu_min, float mu_max, float f, float k);			// Function that find mu by iteration it to the minimum of chi2
    void FindMuIteration (TTree *tree, float mu, float *chi2, float *chi2_error, int *n, float *sigma, float f, float k);			                                // Function that find mu by iteration it to the minimum of chi2
        
    Float_t GetChi2 (void) const;																                                                                    // Function for chi2 counting
	Float_t GetChi2Error (void) const;															                                                                    // Function for chi2 error counting
        
    Float_t NBD(Float_t n, Float_t mu, Float_t k) const;										                                                        			// Function for NBD counting with parameters mu and k
    void SetNBDhist(Float_t mu, Float_t k);												                                                                			// Setting of NBD distribution with parameters mu and k

    float Nancestors(float f) const;												                                                                      			// Function for counting amount of ancestors in one event
    float NancestorsMax(float f) const;														                                                                    	// Function for counting maximum amount of ancestors in one event
        
    std::unique_ptr<TH1F> GetModelHisto (const Float_t range[2], const TString& name, const Float_t par[4]);                                                               // Returns model histogram with known parameters
        
//         
//  Setters
//         
    void SetInputHisto (const TH1F &h)   { fDataHisto = h; }											                      	// Setting of data histogram
    void SetInputHisto2D (const TH2F &h) { fDataHisto2D = h; }											                      	// Setting of data histogram in case of 2D
    void SetFitMinBinX  (Int_t min)      { fFitMinBin[0] = min; }											                   	// Setting of minimal bin for fitting along X axis
    void SetFitMaxBinX  (Int_t max)      { fFitMaxBin[0] = max; }											                   	// Setting of maximal bin for fitting along X axis
    void SetFitMinBinY  (Int_t min)      { fFitMinBin[1] = min; }											                   	// Setting of minimal bin for fitting along Y axis
    void SetFitMaxBinY  (Int_t max)      { fFitMaxBin[1] = max; }											                   	// Setting of maximal bin for fitting along Y axis
    void SetnMuIter (Int_t nMuIter)     { fnMuIter = nMuIter; }												                    // Setting of number of iterations of finding better mu (with same f and k)
    void SetOutDirName (const TString& name)    { fOutDirName = name; }										                	// Setting of the name of directory for output files
	void SetOutFileIDName (const TString& name) { fOutFileIDName = name; }										            	// Setting of ID of output files (ending of all output files of one job will have same ID)
	void SetAncestor_Mode (const TString& Ancestor_Mode) { fAncestor_Mode = Ancestor_Mode; }							    	// Setting of the mode for counting ancestors
	void SetMode (const TString& Mode) { fMode = Mode; }					                                                  	// Setting of the mode for fitting procedure
    void SetHistoMode (const TString& HistoMode) { fHistoMode = HistoMode; }					                              	// Setting of the mode for input histogram
    void SetFit_Mode (const TString& Fit_Mode) { fFit_Mode = Fit_Mode; }							                            // Setting of the mode for fitting procedure ("GoldenSection" or "Iteration")
	void SetGlauber_filename (const TString& Glauber_filename) { fGlauber_filename = Glauber_filename; }						// Setting of input file with Glauber Tree
	void SetGlauber_treename (const TString& Glauber_treename) { fGlauber_treename = Glauber_treename; }						// Setting of the name of tree with GlauberMC model
	void SetDataHisto_filename (const TString& DataHisto_filename) { fDataHisto_filename = DataHisto_filename; }				// Setting of input file with data histo
	void SetDataHisto_name (const TString& DataHisto_name) { fDataHisto_name = DataHisto_name; }							    // Setting of the name of data histo
    void SetNEvents (Int_t Events) { fnEvents = Events; }                                                                       // Setting of number MC Glauber of events
	void SetAProj (Float_t A) { fAProj = A; }														                            // Setting of mass number of projectile nucleus
    void SetATarg (Float_t A) { fATarg = A; }														                            // Setting of mass number of target nucleus
    void SetZProj (Float_t Z) { fZProj = Z; }														                            // Setting of charge number of projectile nucleus
    void SetZTarg (Float_t Z) { fZTarg = Z; }														                            // Setting of charge number of target nucleus
    void SetEBeam (Float_t E) { fEBeam = E; }														                            // Setting of energy of beam
    void SetEstimatorStepX ( Int_t EstimatorStep ) { fEstimatorStep[0] = EstimatorStep; };		            					// Setting of step of variating lower and upper multiplicity range along X axis
	void SetMinEstimatorX ( Int_t MinEstimator ) { fMinEstimator[0] = MinEstimator; };				            			    // Setting of not fitting low multiplicity region along X axis due to trigger bias, etc
	void SetMaxEstimatorX ( Int_t MaxEstimator ) { fMaxEstimator[0] = MaxEstimator; };				            			    // Setting of very large number to fit the whole histo along X axis
	void SetMinFitRangeX ( Int_t MinFitRange ) { fMinFitRange[0] = MinFitRange; };										        // Setting of minimal multiplicity range for fitting along X axis
    void SetEstimatorStepY ( Int_t EstimatorStep ) { fEstimatorStep[1] = EstimatorStep; };				            			// Setting of step of variating lower and upper multiplicity range along Y axis
    void SetMinEstimatorY ( Int_t MinEstimator ) { fMinEstimator[1] = MinEstimator; };					            		    // Setting of not fitting low multiplicity region along Y axis due to trigger bias, etc
    void SetMaxEstimatorY ( Int_t MaxEstimator ) { fMaxEstimator[1] = MaxEstimator; };					            		    // Setting of very large number to fit the whole histo along X axis
    void SetMinFitRangeY ( Int_t MinFitRange ) { fMinFitRange[1] = MinFitRange; };										        // Setting of minimal multiplicity range for fitting along X axis
    void Set_kMin ( Float_t kMin ) { f_kMin = kMin; };													                        // Setting of lower parameter k
	void Set_kMax ( Float_t kMax ) { f_kMax = kMax; };													                        // Setting of upper parameter k
	void Set_kStep ( Float_t kStep ) { f_kStep = kStep; };												                       	// Setting of step of variating of parameter k
	void Set_fMin ( Float_t fMin ) { f_fMin = fMin; };													                        // Setting of lower parameter f
	void Set_fMax ( Float_t fMax ) { f_fMax = fMax; };													                        // Setting of upper parameter f
    void Set_fStep ( Float_t fStep ) { f_fStep = fStep; };												                    	// Setting of step of variating of parameter f
	void Set_muStep ( Float_t muStep ) { f_muStep = muStep; };											                        // Setting of step of variating of parameter mu
	void Set_MuMinPercentage ( Float_t MuMinPercentage ) { f_MuMinPercentage = MuMinPercentage; };								// Setting of lower mu in percent for first iteration
	void Set_MuMaxPercentage ( Float_t MuMaxPercentage ) { f_MuMaxPercentage = MuMaxPercentage; };								// Setting of upper mu in percent for first iteration
    void SetYSigma (Float_t YSigma) { fYSigma = YSigma; };										                                // Setting constant parameter for rapidity shift sampling


//
//  Getters
//      
	TString GetOutFileIDName () const { return fOutFileIDName; }												                                        // Returns ID of output files (its ending)
	TString GetGlauber_filename () { return fGlauber_filename; }												                                        // Returns input file with Glauber Tree
	TString GetGlauber_treename () { return fGlauber_treename; }                                        												// Returns the name of tree with
	TString GetDataHisto_filename () { return fDataHisto_filename; }									                                        	    // Returns input file with data histo
	TString GetDataHisto_name () { return fDataHisto_name; }												                                            // Returns the name of data histo

    TString GetMode ()   const   { return fMode; }					                                                                                    // Returns the mode for fitting function
    TString GetHistoMode ()   const   { return fHistoMode; }					                                                                        // Returns the mode for input histogram
    TString GetFit_Mode ()   const   { return fFit_Mode; }							                                                                    // Returns the mode for fitting procedure ("GoldenSection" or "Iteration")
    Int_t GetFitMinBinX  ()   const   { return fFitMinBin[0]; }													                                        // Returns minimal bin for fitting along X axis
    Int_t GetFitMaxBinX  ()   const   { return fFitMaxBin[0]; }			                                            									// Returns maximal bin for fitting along X axis
	Int_t GetEstimatorStepX ()   const   { return fEstimatorStep[0]; };									                                                // Returns step of variating lower and upper multiplicity range along X axis
	Int_t GetMinEstimatorX ()   const   { return fMinEstimator[0]; };			                                						                // Returns not fitting low multiplicity region along X axis due to trigger bias, etc
	Int_t GetMaxEstimatorX ()   const   { return fMaxEstimator[0]; };									                                                // Returns very large number to fit the whole histo along X axis
	Int_t GetMinFitRangeX ()   const   { return fMinFitRange[0]; };											                                            // Returns minimal multiplicity range for fitting along X axis
    Int_t GetFitMinBinY  ()   const   { return fFitMinBin[1]; }													                                        // Returns minimal bin for fitting along Y axis
    Int_t GetFitMaxBinY  ()   const   { return fFitMaxBin[1]; }			                                            						    		// Returns maximal bin for fitting along Y axis
    Int_t GetEstimatorStepY ()   const   { return fEstimatorStep[1]; };									                                                // Returns step of variating lower and upper multiplicity range along Y axis
    Int_t GetMinEstimatorY ()   const   { return fMinEstimator[1]; };			                                						                // Returns not fitting low multiplicity region along Y axis due to trigger bias, etc
    Int_t GetMaxEstimatorY ()   const   { return fMaxEstimator[1]; };									                                                // Returns very large number to fit the whole histo along Y axis
    Int_t GetMinFitRangeY ()   const   { return fMinFitRange[1]; };                                                                                     // Returns minimal multiplicity range for fitting along Y axis
    Float_t Get_kMin ()   const   { return f_kMin; };													                                                // Returns lower parameter k
	Float_t Get_kMax ()   const   { return f_kMax; };												                                                  	// Returns upper parameter k
	Float_t Get_kStep ()   const   { return f_kStep; };												                                                	// Returns step of variating of parameter
	Float_t Get_fMin ()   const   { return f_fMin; };													                                                // Returns lower parameter f
	Float_t Get_fMax ()   const   { return f_fMax; };										                                                   			// Returns upper parameter f
	Float_t Get_fStep ()   const   { return f_fStep; };										                                                			// Returns step of variating of parameter f
	Float_t Get_muStep ()   const   { return f_muStep; };										                                            			// Returns step of variating of parameter mu
    Float_t GetYSigma ()   const   { return fYSigma; };										                                            	    		// Returns constant parameter for rapidity shift sampling


    TH1F GetGlauberFitHisto () const { return fGlauberFitHisto; }								                                        				// Returns model histogtam
	TH1F GetBestFitHisto ()    const { return fBestFitHisto;  }										                                            		// Returns model histogtam with minimal chi2
    TH1F GetDataHisto ()       const { return fDataHisto;  }											                                            	// Returns data histogram
    TH2F GetGlauberFitHisto2D () const { return fGlauberFitHisto2D; }							                                        				// Returns model histogtam in 2D case
    TH2F GetBestFitHisto2D ()    const { return fBestFitHisto2D;  }									                                            		// Returns model histogtam with minimal chi2 in 2D case
    TH2F GetDataHisto2D ()       const { return fDataHisto2D;  }										                                            	// Returns data histogram in 2D case
    TH1F GetSampleHisto ()        const { return fSampleHisto;   }												                                        // Returns histogram of either NBD or Gauss distribution
        
	std::map <TString, TH1F*> GetMapOfGlauber_Parameters_Histos () const { return Glauber_Parameters_Histos; }						                    // Returns map with historams of parameters of GlauberMC input file
	std::map <TString, TH2F*> GetMapOfGlauber_Parameters_VS_Estimator_Histos () const { return Glauber_Parameters_VS_Estimator_Histos; }		        // Returns map with historams of parameters of GlauberMC input file versus modeled multiplicity
	std::map <TString, TH2F*> GetMapOfGlauber_Parameters_VS_Estimator_BestHistos () const { return Glauber_Parameters_VS_Estimator_BestHistos; }	    // Returns map with historams of parameters of GlauberMC input file versus modeled multiplicity with minimal #chi^{2}
    std::map <TString, TH3F*> GetMapOfGlauber_Parameters_VS_Estimator_Histos3D () const { return Glauber_Parameters_VS_Estimator_Histos3D; }		    // Returns map with historams of parameters of GlauberMC input file versus modeled multiplicity in 3D case
    std::map <TString, TH3F*> GetMapOfGlauber_Parameters_VS_Estimator_BestHistos3D () const { return Glauber_Parameters_VS_Estimator_BestHistos3D; }	// Returns map with historams of parameters of GlauberMC input file versus modeled multiplicity with minimal #chi^{2} in 3D case

    private:

    /**   Data members  **/

	TH1F fDataHisto;
    TH2F fDataHisto2D;
    TH1F fSampleHisto;
    TH1F fGlauberFitHisto;
    TH2F fGlauberFitHisto2D;
    TH1F fBestFitHisto;
    TH2F fBestFitHisto2D;

	std::map <TString, TH1F*> Glauber_Parameters_Histos;       
	std::map <TString, TH2F*> Glauber_Parameters_VS_Estimator_Histos;
	std::map <TString, TH2F*> Glauber_Parameters_VS_Estimator_BestHistos;
    std::map <TString, TH3F*> Glauber_Parameters_VS_Estimator_Histos3D;
    std::map <TString, TH3F*> Glauber_Parameters_VS_Estimator_BestHistos3D;
        
    /* MC data */
    std::unique_ptr<TTree> fSimTree{nullptr};
        
	Float_t fAProj{-1.}; // Mass number of projectile nucleus
    Float_t fATarg{-1.}; // Mass number of target nucleus
    Float_t fZProj{-1.}; // Charge number of projectile nucleus
    Float_t fZTarg{-1.}; // Charge number of target nucleus
    Float_t fEBeam{-1.}; // Energy number of projectile beam

	std::map <TString, Float_t> Glauber_Parameters = {
		{"Npart", -1.},                   // Number of participating nucleons
        {"Ncoll", -1.},                   // Number of binary collisions
		{"Nhard", -1.},                   // Number of hard collisions (with hard particle production)
		{"B", -1.},                       // Generated impact parameter, fm
        {"BNN", -1.},                     // Mean nucleon–nucleon impact parameter, fm
		{"Ncollpp", -1.},                 // Number of pp collisions
		{"Ncollpn", -1.},                 // Number of pn collisions
		{"Ncollnn", -1.},                 // Number of nn collisions
		{"VarX", -1.},                    // Variance of x for wounded nucleons, σ^2_x, fm^2
		{"VarY", -1.},                    // Variance of y for wounded nucleons, σ^2_y, fm^2
		{"VarXY", -1.},                   // Covariance of x and y for wounded nucleons, σ_xy ≡ <xy> − <x><y>, fm^2
		{"NpartA", -1.},                  // Number of participating nucleons from nucleus A
		{"NpartB", -1.},                  // Number of participating nucleons from nucleus B
		{"Npart0", -1.},                  // Number of singly-wounded participating nucleons
		{"AreaW", -1.},                   // Area defined by width of participants, fm^2
		{"Psi1", -1.},                    // Event plane angle of 1st harmonic, rad
		{"Ecc1", -1.},                    // Participant eccentricity for 1st harmonic
		{"Psi2", -1.},                    // Event plane angle of 2nd harmonic, rad
		{"Ecc2", -1.},                    // Participant eccentricity for 2nd harmonic
		{"Psi3", -1.},                    // Event plane angle of 3rd harmonic, rad
		{"Ecc3", -1.},                    // Participant eccentricity for 3rd harmonic
		{"Psi4", -1.},                    // Event plane angle of 4th harmonic, rad
		{"Ecc4", -1.},                    // Participant eccentricity for 4th harmonic
		{"Psi5", -1.},                    // Event plane angle of 5th harmonic, rad
		{"Ecc5", -1.},                    // Participant eccentricity for Nth harmonic
		{"AreaO", -1.},                   // Area by ”or” of participants in grid
		{"AreaA", -1.},                   // Area by ”and” of participants in grid
		{"X0", -1.},                      // Production point in x, fm
		{"Y0", -1.},                      // Production point in y, fm
		{"Phi0", -1.},                    // Direction in phi
		{"Length", -1.},                  // Length in phi0
		{"MeanX", -1.},                   // Mean of x for wounded nucleons, <x>, fm
		{"MeanY", -1.},                   // Mean of y for wounded nucleons, <y>, fm
		{"MeanX2", -1.},                  // Mean of x^2 for wounded nucleons, <x^2>, fm^2
		{"MeanY2", -1.},                  // Mean of y^2 for wounded nucleons, <y^2>, fm^2
		{"MeanXY", -1.},                  // Mean of xy for wounded nucleons, <xy>, fm^2
		{"MeanXSystem", -1.},             // Mean of x for all nucleons, fm^2
		{"MeanYSystem", -1.},             // Mean of y for all nucleons, fm^2
		{"MeanXA", -1.},                  // Mean of x for nucleons in nucleus A, fm^2
		{"MeanYA", -1.},                  // Mean of y for nucleons in nucleus A, fm^2
		{"MeanXB", -1.},                  // Mean of x for nucleons in nucleus B, fm^2
		{"MeanYB", -1.},                  // Mean of y for nucleons in nucleus B, fm^2
		{"PhiA", -1.},                    // Azimuthal angle for nucleus A, rad
		{"ThetaA", -1.},                  // Polar angle for nucleus A, rad
		{"PhiB", -1.},                    // Azimuthal angle for nucleus B, rad
		{"ThetaB", -1.},                  // Polar angle for nucleus B, rad
    };

	std::map <TString, const int> Glauber_ParametersMax;
	std::map <TString, const int> Glauber_ParametersMin;

    Float_t fMaxValue[2]{-1, -1};
    Int_t fNbins[2]{-1, -1};
        
	Int_t fnEvents;

	Int_t fnMuIter{2};

	Int_t fFitMinBin[2]{-1, -1};
    Int_t fFitMaxBin[2]{-1, -1};
	Int_t fEstimatorStep[2]{1, 1};
	Int_t fMinEstimator[2]{1, 1};
	Int_t fMaxEstimator[2]{100, 100};
	Int_t fMinFitRange[2]{4, 4};
	Float_t f_kMin{1.0};                                   // Width value of either NBD (for multiplicity) or Gauss (for energy)
	Float_t f_kMax{1.0};
	Float_t f_kStep{0.2};
	Float_t f_fMin{0.0};
	Float_t f_fMax{1.0};
	Float_t f_fStep{0.1};
    Float_t f_muStep{0.01};                                // Width value of either NBD (for multiplicity) or Gauss (for energy)
	Float_t f_MuMinPercentage{0.7};
	Float_t f_MuMaxPercentage{1.3};
    Float_t fYSigma{1.0};                                  // Constant parameter for rapidity shift sampling
        
    TString fAncestor_Mode{"Default"};                  // Default/Nspec/NspecProj/NspecTarg/Npart/Ncoll
	TString fMode{"Multiplicity"};                      // Multiplicity/Energy/RapidityVSEnergy
    TString fHistoMode{"1D"};                           // 1D/2D
    TString fFit_Mode{"GoldenSection"};                 // GoldenSection/Iteration
	TString fGlauber_filename{""};
	TString fGlauber_treename{""};
	TString fDataHisto_filename{""};
	TString fDataHisto_name{""};
        
    TString fOutDirName{""};
	TString fOutFileIDName {""};
    ClassDef(Fitter, 2);
        
    };
}

#endif
