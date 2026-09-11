/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "comment.hpp"


CommentNode::CommentNode(const Window& _window, float _X, float _Y, const char* _val)
: Node(_window, _X, _Y, Textures::BlockLongWait),
typer(_window, {_X-0.055f, _Y-0.002f, .height=GUI::Medium,
    .horAli=GUI::Left, .textColor=BLACK, .backColor=WHITE}, 17, _val) {}

Node* CommentNode::copy() {
    return new CommentNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), typer.getString()};
}

void CommentNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    typer.move(_X, _Y);
}

void CommentNode::checkOff(const Mouse _mouse) {
    typer.checkOff(_mouse);
}

GUI::Code CommentNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (typer.click(_mouse)) {
            return GUI::Button1;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void CommentNode::unclick() {
    typer.unclick();
}

void CommentNode::type(SDL_Keycode _code) {
    typer.type(_code);
}

void CommentNode::writeString(const char* _str) {
    typer.writeString(_str);
}

void CommentNode::update(float _mouseX) {
    typer.update(_mouseX);
}

void CommentNode::blit() const {
    Node::blit();
    typer.blit();
}

Node* CommentNode::use() {
    logger.additional("> Comment");
    return nextNode;
}

void CommentNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'c');
    SDL_IOprintf(_fout, " %s", typer.getString());
}
