#ifndef CONFIG_H
#define CONFIG_H

// DECLARATIONS only — telling other files these exist
extern int MAX_CONNECTIONS;
extern float timeout;

void update_config(void);
void reset_config(void);

#endif
