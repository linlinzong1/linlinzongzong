#include "database/Database.h"

int main()
{
    Database db;
    if (!db.open("linlinzongzong.db")) {
        return -1; // Exit if the database cannot be opened
    }

    if (!db.createTables()) {
        return -1; // Exit if tables cannot be created
    }

    // Additional application logic can go here

    db.close();
    return 0;
}