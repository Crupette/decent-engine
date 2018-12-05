#include "GuiManager.h"
#include "Base.h"
#include "RendererDefault.h"

namespace DecentEngine {

Camera GuiManager::m_camera;
GuiManager::GuiMap GuiManager::m_guis;
GuiManager::ActiveIdMap GuiManager::m_active;

void GuiManager::init(){
	glm::uvec2 screenDims = Base::getWindow()->getSize();
	m_camera.init(glm::vec2(screenDims.x / 2, screenDims.y / 2), 1.f, 0.f);
	m_camera.update(Base::getWindow());
}

void GuiManager::destroy(){
	for(auto i = m_guis.begin(); i != m_guis.end(); i++){
		delete i->second;
	}
}

void GuiManager::update(){
	if(Base::wasScreenResized()){
		glm::uvec2 screenDims = Base::getWindow()->getSize();
		m_camera.setPosition(glm::vec2(screenDims) / glm::vec2(2.f));
		m_camera.update(Base::getWindow());
	}
	for(auto i = m_active.begin(); i != m_active.end(); i++){
		m_guis.find(i->first)->second->update();
	}
}

void GuiManager::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	for(auto i = m_active.begin(); i != m_active.end(); i++){
		m_guis.find(i->first)->second->render();
	}

	DecentEngine::RendererDefault::end();
}

void GuiManager::addGui(const std::string& id, Gui* gui){
	m_guis.emplace(id, gui);
	if(gui->type == Gui::Type::CONST){
		m_active.emplace(id, true);
	}else{
		m_active.emplace(id, false);
	}
}
bool GuiManager::setGui(const std::string& id, bool mode){
	auto result = m_active.find(id);
	if(result == m_active.end()) return false;
	if(mode == false){
		result->second = false;
		return true;
	}
	if(m_guis.find(result->first)->second->type == Gui::Type::INTERRUPT){
		for(auto i = m_active.begin(); i != m_active.end(); i++){
			auto gui = m_guis.find(i->first);
			if(gui->second->type == Gui::Type::CONST) continue;
			i->second = false;
		}
	}
	result->second = true;
	return true;
}

}
