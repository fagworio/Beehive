///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2016 Matt Phillips, Big Evil Corporation
///////////////////////////////////////////////////////

#pragma once

#include "UIBase.h"
#include "../Project.h"
#include "../GameObject.h"

class MainWindow;

class GameObjectParamsPanel : public GameObjParamsPanelBase
{
public:
	GameObjectParamsPanel(MainWindow& mainWindow, Project& project, wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER, const wxString& name = wxPanelNameStr);

	virtual void Refresh(bool eraseBackground = true, const wxRect *rect = NULL);
	virtual void OnToolVariableAdd(wxCommandEvent& event);
	virtual void OnToolVariableRemove(wxCommandEvent& event);
	virtual void OnSelectVariable(wxListEvent& event);
	virtual void OnBtnApplyChanges(wxCommandEvent& event);
	
	void SetGameObject(GameObject* gameObject);

private:
	void PopulateVarsList();
	void PopulateVarsFields(GameObjectVariable* variable);

	Project& m_project;
	MainWindow& m_mainWindow;

	GameObject* m_gameObject;
	GameObjectVariable* m_currentVariable;
};