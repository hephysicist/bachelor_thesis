{
        const int strL = 6;	
	double buf[strL];	
	int count = 0;
	TTree *t1 = new TTree("t1","t1");	
	t1->Branch("Ud",&buf[0],"Ud/D");
	t1->Branch("Ug1u",&buf[1],"Ug1u/D");
	t1->Branch("Ug1d",&buf[2],"Ug1d/D");
	t1->Branch("Ug2u",&buf[3],"Ug2u/D");
	t1->Branch("Ug2d",&buf[4],"Ug2d/D");
	t1->Branch("Uc",&buf[5],"Uc/D");
	ifstream inputFile;
	inputFile.open("Raether_exp.dat");
	while(!inputFile.eof()){
		for(int i = 0; i < strL; i++){
			inputFile >> buf[i];		
		}
		t1->Fill();
		count++;
		//printf("Fill %d element\n",count);		
	}	
	inputFile.close();
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	t1->SetMarkerStyle(7);
	t1->Draw("Uc:Ug2d","Ug1u-Ug1d==300 && Ug2d<=1800");
	TGraph * gr1 = (TGraph*)c1->GetPrimitive("Graph")->Clone("gr1");
	t1->Draw("Uc:Ug2d","Ug1u-Ug1d==420 && Ug2d<=1800");
	TGraph * gr2 = (TGraph*)c1->GetPrimitive("Graph")->Clone("gr2");
	Double_t X;
	Double_t Y1;
	Double_t Y2;
	Double_t YError;	
	TGraphErrors * ratioGr = new TGraphErrors();
	for(int i = 0; i < 4; i++){
		gr1->GetPoint(i,X,Y1);
		gr2->GetPoint(i,X,Y2);
		printf("%lf\t%lf\t%lf\n",X,Y1,Y2);		
		ratioGr->SetPoint(i,X,Y2/Y1);
		YError = Y2/Y1*sqrt((0.1/Y1)*(0.1/Y1)+(0.1/Y2)*(0.1/Y2));		
		ratioGr->SetPointError(i,0,YError);	
	}
	ratioGr->GetXaxis()->SetTitle("Induction gap voltage, V");
	ratioGr->GetYaxis()->SetTitle("Signal ratio");
	ratioGr->SetMarkerStyle(7);
	ratioGr->Draw("AP");
}
	
