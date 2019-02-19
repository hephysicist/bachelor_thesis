{
	const int strL = 6;	
	double buf[strL];	
	TTree *t1 = new TTreee("","","Ud:Ug1u:Ug1d:Ug2u:Ug2d:Uc");	
	t1->Branch("Ud",&buf[0],"Ud/D");
	t1->Branch("Ug1u",&buf[1],"Ug1u/D");
	t1->Branch("Ug1d",&buf[2],"Ug1d/D");
	t1->Branch("Ug2u",&buf[3],"Ug2u/D");
	t1->Branch("Ug2d",&buf[4],"Ug2d/D");
	t1->Branch("Uc",&buf[5],"Uc/D");
	ifstream *inputFile;
	inputFile->open("Raether_exp.dat");
	while(!inputFile->eof()){
		for(nt i = 0; i < strL; i++){
			inputFile >> buf[i];		
		}
		t1->Fill();		
	}	
	
}
	
