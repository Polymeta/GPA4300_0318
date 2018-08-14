#pragma once

/// <summary>
/// world class
/// </summary>
class GWorld
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GWorld() {}
	
	/// <summary>
	/// destructor
	/// </summary>
	~GWorld() {}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize world
	/// </summary>
	/// <param name="_pFileName">file name</param>
	void Init(const char* _pFileName);
#pragma endregion
};