/****************************************************************************
* AMLibExample								    *
* File: AMLibExample.cpp						    *
*									    *
* Author : Lukasz Wandzik						    *
* This is an example of AMLib usage				            *
****************************************************************************/
#include <iostream>
#include <ShapeModel.h>
#include <TextureModel.h>
#include <CombinedModel.h>

using namespace AMLIB;
using namespace ULIB;

void usage(void)
{
	std::cout << "Usage: " << std::endl
			  << "\t	 " << std::endl
			  << "\t-m	: Model to build ('s' - shape, 't' - texture, 'c' - combined)" << std::endl
			  << "\t-p	: Path to the point files (input)" << std::endl
			  << "\t-i	: Path to the image files (input)" << std::endl
			  << "\t-o	: Path and name of the model file (output)" << std::endl
			  << "\t-ep	: Extension of the point files ([.asf|.pts])" << std::endl
			  << "\t-ei	: Extension of the image files" << std::endl
			  << "\t-vs	: Variance to retain for the shpe model (default: 0.95 - > 95%)" << std::endl
			  << "\t-vt	: Variance to retain for the texture model (default: 0.95 - > 95%)" << std::endl
			  << "\t-vc	: Variance to retain for the combined model (default: 0.95 - > 95%)" << std::endl
			  << "\t-c	: Number of color channels [1|3] (default: 1)" << std::endl
			  << "\t-s	: Scale parameter (0 - 1, default: 0)" << std::endl
			  << "\t-n	: Number of samples to process" << std::endl
			  << "\t-norm	: Normalize texture data [0|1] (default: 0)" << std::endl;
}

int main(int argc, const char** argv)
{
	ShapeModel *shm = NULL;
	TextureModel *txm = NULL;
	CombinedModel *cbm = NULL;

	char model;
	Options opt;
	std::string dirS, dirI, dirO;

	// Parse command line
	for(int i = 1; i < argc; i++)
	{
		if(std::strcmp(argv[i], "-m") == 0)
		{
			if(argc > i + 1){ model = *argv[i + 1]; } else { model = 0; }
		}
		if(std::strcmp(argv[i], "-p") == 0)
		{
			if(argc > i + 1) { dirS = argv[i + 1]; } 
		}
		if(std::strcmp(argv[i], "-i") == 0)
		{
			if(argc > i + 1) { dirI = argv[i + 1]; } 
		}
		if(std::strcmp(argv[i], "-o") == 0)
		{
			if(argc > i + 1) { dirO = argv[i + 1]; } 
		}
		if(std::strcmp(argv[i], "-ep") == 0)
		{
			if(argc > i + 1) { opt.shapeFileExt = argv[i + 1]; } 
		}
		if(std::strcmp(argv[i], "-ei") == 0)
		{
			if(argc > i + 1) { 	opt.imageFileExt = argv[i + 1]; } 
		}
		if(std::strcmp(argv[i], "-vs") == 0)
		{
			if(argc > i + 1) { opt.varToRetainS = std::atof(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-vt") == 0)
		{
			if(argc > i + 1) { opt.varToRetainT  = std::atof(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-vc") == 0)
		{
			if(argc > i + 1) { opt.varToRetainC = std::atof(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-c") == 0)
		{
			if(argc > i + 1) { opt.nChannels = std::atoi(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-n") == 0)
		{
			if(argc > i + 1) { opt.nSamples  = std::atoi(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-s") == 0)
		{
			if(argc > i + 1) { opt.scale = std::atof(argv[i + 1]); } 
		}
		if(std::strcmp(argv[i], "-norm") == 0)
		{
			if(argc > i + 1) { opt.normalizeTex = std::atoi(argv[i + 1]); } 
		}
	}
	if(model == 0 || dirS.empty() ||  dirI.empty() ||  dirO.empty() || opt.shapeFileExt.empty() || opt.imageFileExt.empty())
	{
		usage();
		exit(-1);
	}

	switch(model)
	{
	case 's':
		{
			shm = new ShapeModel(dirS,  opt);	
			shm->writeModel(dirO);
		}
		break;
	case 't':
		{
			txm = new TextureModel(dirS, dirI, opt);
			txm->writeModel(dirO);
		}
		break;
	case 'c':
		{
			cbm = new CombinedModel(dirS, dirI, opt);
			cbm->writeModel(dirO);
		}
		break;
	default:
		std::cerr << "Unknown model type!" << std::endl;
		break;
	}
	if(shm != NULL)
	{
		delete shm;
	}
	if(txm != NULL)
	{
		delete txm;
	}
	if(cbm != NULL)
	{
		delete cbm;
	}
	return 0;
}
