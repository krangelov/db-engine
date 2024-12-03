#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "text.h"
#include "namespace.h"

typedef struct {
    int value;
    PgfText name;
} Property;

typedef struct {
    int x,y;
    Namespace<Property> properties;
} Point;

const char *COLOR_NAME = "color";

int main()
{
    PgfDB db("test.db", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR, 7*4096);

    {
        // Before accessing a database we must activate it.
        DB_scope scope(&db, WRITER_SCOPE);

        //Now we start a write transaction
        db.start_transaction();
        
        // Allocate and initialize a new root object
        ref<Point> point = PgfDB::malloc<Point>();
        point->x = 10;
        point->y = 20;
        point->properties = 0;
        db.set_transaction_object(point.as_object());

        // Points can have properties. Just to illustrate how to use search trees.
        ref<Property> prop = PgfDB::malloc<Property>(strlen(COLOR_NAME)+1);
        prop->value = 0xFF0000;
        prop->name.size = strlen(COLOR_NAME);
        strcpy(prop->name.text, COLOR_NAME);

        // Insert the property in the search tree (the namespace)
        Namespace<Property> new_properties =
            namespace_insert(point->properties, prop);
        point->properties = new_properties;

        db.commit(point.as_object());
    }

    {
        // Activate the database for reading
        DB_scope scope(&db, READER_SCOPE);

        // Get the root object from the database
        ref<Point> point = db.get_active_object();
        printf("%d %d\n", point->x, point->y);
        
        // Example for searching in the database
        PgfText *name = string2text(COLOR_NAME);
        Property *prop = namespace_lookup(point->properties, name);
        printf("%x\n", prop->value);
        free(name);
    }

    return 0;
}
