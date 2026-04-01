/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../GUI/interface.hpp"
#include "../serial/serial.hpp"


// Class for storing collected data and show it
class CollectedData : public GUI::Template {
 private:
    /* data */

 public:
    CollectedData(const Window& window);
    ~CollectedData();
    void update();
    void blit() const override;

    // Interacting with files
    void save(const char* name);
};
