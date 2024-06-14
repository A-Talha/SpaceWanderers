#ifndef UI_Functions
#define UI_Functions

void drawText(const char *text, float x, float y, void *font);
void drawStrokedText(const char* text, float x, float y, float scale);
void drawRectangle(float x, float y, float width, float height);
void drawHealthBar(float x, float y, float width, float height, float maxHealth, float currentHealth);
void decreaseHealth(int amount);
void increaseHealth(int amount);

#endif