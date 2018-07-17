#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region forward decleration
class CRenderer;
class CObject;
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// content management system
/// </summary>
class CContentManagement
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CContentManagement() {}

	/// <summary>
	/// destructor
	/// </summary>
	~CContentManagement();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// add object to scene list
	/// </summary>
	/// <param name="_pObject">object to add</param>
	inline void AddSceneObject(CObject* _pObject) { AddObject(_pObject, m_pSceneObjects); }

	/// <summary>
	/// add object to persitant list
	/// </summary>
	/// <param name="_pObject">object to add</param>
	inline void AddPersistantObject(CObject* _pObject) { AddObject(_pObject, m_pPersistantObjects); }

	/// <summary>
	/// add object to ui list
	/// </summary>
	/// <param name="_pObject">object to add</param>
	inline void AddUIObject(CObject* _pObject) { AddObject(_pObject, m_pUIObjects); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	/// <param name="_pRenderer">renderer</param>
	void Render(CRenderer* _pRenderer);

	/// <summary>
	/// remove object
	/// </summary>
	/// <param name="_pObj">object to remove</param>
	void RemoveObject(CObject* _pObj);

	/// <summary>
	/// sort list for layering
	/// </summary>
	/// <param name="_pList">list to sort</param>
	void SortList(list<CObject*> &_pList);
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// scene / world objects
	/// </summary>
	list<CObject*> m_pSceneObjects;

	/// <summary>
	/// persistant object
	/// </summary>
	list<CObject*> m_pPersistantObjects;

	/// <summary>
	/// ui / screen object
	/// </summary>
	list<CObject*> m_pUIObjects;

	/// <summary>
	/// objects to remove
	/// </summary>
	list<CObject*> m_pRemoveObjects;
#pragma endregion

#pragma region private function
	/// <summary>
	/// add object to list
	/// </summary>
	/// <param name="_pObj">object</param>
	/// <param name="_pList">list to add to</param>
	void AddObject(CObject* _pObj, list<CObject*> &_pList);
#pragma endregion
};