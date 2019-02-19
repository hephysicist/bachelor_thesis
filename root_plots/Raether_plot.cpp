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
	t1->Draw("Uc:Ug2d","Ug1u-Ug1d==300");
	TGraph * gr1 = (TGraph*)c1->GetPrimitive("Graph")->Clone("gr1");
	t1->Draw("Uc:Ug2d","Ug1u-Ug1d==420");
	TGraph * gr2 = (TGraph*)c1->GetPrimitive("Graph")->Clone("gr2");
	Double_t YError = 1e-4; // V	
	Double_t X, Y; //X - gap voltage [V] Y - voltage on the collector circut resisstor [mV]
		       // R = 5MOhm
	Double_t d = 0.15; // cm 
	Double_t R = 2.22e6; // Ohm - R1/(1+R1/Rv)^2
	int i = 0;
	TGraphErrors * gr1err = new TGraphErrors();
	TGraphErrors * gr2err = new TGraphErrors();
	while(i < gr2->GetN()){	
		gr1->GetPoint(i,X,Y);
		printf("Get i %d\tX %lf\tY %lf\n",i, X, Y);
		gr1err->SetPoint(i,X/d/1e3,Y*1e-3/R);
		gr1err->SetPointError(i,0,YError/R);			
		i++;
		
	}
	i = 0;
	while(i < gr2->GetN()){
		gr2->GetPoint(i,X,Y);
		gr2err->SetPoint(i,X/d/1e3,Y*1e-3/R);
		gr2err->SetPointError(i,0,YError/R);		
		i++;
		printf("Get i %d\tX %lf\tY %lf\n",i, X, Y);
	}
	gr1err->GetXaxis()->SetTitle("Induction gap field, kV/cm");
	gr1err->GetYaxis()->SetTitle("Anode current, A");
	gr1err->SetMarkerStyle(22);
	gr1err->SetMarkerSize(2);
	gPad->SetLogy();
	gr1err->GetYaxis()->SetRangeUser(1e-11,1e-8);
	gr1err->GetXaxis()->SetLimits(5,16);
	gr1err->Draw("AP");
	gr2err->SetMarkerStyle(21);
	gr2err->SetMarkerSize(2);
	gr2err->Draw("P SAME");
 	auto legend = new TLegend(0.7,0.8,0.93,0.93);
   	legend->AddEntry(gr1err,"U_{GEM1} = 300 V","pe");
   	legend->AddEntry(gr2err,"U_{GEM1} = 450 V","pe");
   	legend->Draw();
	
	c1->Update();
}
	
