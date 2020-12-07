struct list;

void insertLast(double data);

double getByIndex(struct list* h, size_t idx);

void insertByIndex(struct list* h, size_t idx, double data);

void removeNode(struct list* h, size_t index);

size_t findMinItemID(struct list * arr);