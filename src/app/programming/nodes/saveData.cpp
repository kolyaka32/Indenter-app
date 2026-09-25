/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveData.hpp"
#include "../../output/collectedData.hpp"


SaveDataNode::SaveDataNode(const Window& _window, float _X, float _Y, const char* _val)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, {"Save as", "Сохранить как"}, {_X-rect.w/(2*window.getWidth())+0.005f, _Y, .horAli=GUI::Left}),
nameTyper(_window, {_X+(LanguagedText::getLanguage()==Language::Russian ? 0.022f : -0.01f), _Y-0.002f,
    .height=GUI::Medium, .horAli=GUI::Left, .textColor=BLACK, .backColor=WHITE}, 6, _val) {}

Node* SaveDataNode::copy() {
    return new SaveDataNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), nameTyper.getString()};
}

void SaveDataNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    nameTyper.move(_X, _Y);
}

void SaveDataNode::checkOff(const Mouse _mouse) {
    nameTyper.checkOff(_mouse);
}

GUI::Code SaveDataNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (nameTyper.click(_mouse)) {
            return GUI::Button1;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void SaveDataNode::unclick() {
    nameTyper.unclick();
}

bool SaveDataNode::type(SDL_Keycode _code) {
    return nameTyper.type(_code);
}

bool SaveDataNode::writeString(const char* _str) {
    return nameTyper.writeString(_str);
}

void SaveDataNode::update(float _mouseX) {
    nameTyper.update(_mouseX);
}

void SaveDataNode::blit() const {
    Node::blit();
    text.blit();
    nameTyper.blit();
}

Node* SaveDataNode::use() {
    collectedData.trySave(nameTyper.getString());
    logger.additional("> Save data");
    return nextNode;
}

void SaveDataNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'a');
}
