#include <startup.h>
#include <libundermine.h>

__attribute__ ((used))
CTOR void libundermine_init(void){
    resource_init();
}

#include <grc.c>
#include <startup.c>
#include <vector/vector.c>
#include <list/list.c>
#include <set/set.c>