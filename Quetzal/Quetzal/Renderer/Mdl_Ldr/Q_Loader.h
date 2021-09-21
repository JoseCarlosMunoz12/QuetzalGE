#pragma once
#include "../Model.h"
#include "../Anim_Model.h"
#include "../AnimHandler.h"
#include "ParsingData.h"

using namespace Q_Parser;
class Q_Loader
{
private:
	
public:
	Q_Loader();
	void LoadQ_File(std::string FileName);
};