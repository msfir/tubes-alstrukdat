#include <assert.h>
#include <fridge.h>

int main() {
    printf("--- Driver Test Fridge ---");
    printf("\n")   ;
    printf("\n")   ;
    Fridge fridge;
    CreateFridge(&fridge, 20, 20);
    assert(fridge.space.colEff == 20);
    assert(fridge.space.rowEff == 20);
    assert(fridge.width == 20);
    assert(fridge.height == 20);
    Food mie_ayam;
    Time exp;
    CreateTime(&exp, 10, 10, 10);
    Time deliv;
    CreateTime(&deliv, 0, 30, 0);
    Time proc;
    CreateTime(&proc, 0, 0, 1);
    CreateFood(&mie_ayam, 99, StringFrom("Mie Ayam"), exp, BUY, deliv, (Size) {2, 2}, proc);
    put_food(&fridge, 5, 5, mie_ayam);
    for (int i = 5; i < 5 + mie_ayam.size.width; i++) {
        for (int j = 5; j < 5 + mie_ayam.size.height; j++) {
            assert(fridge.space.mem[i][j] == 'X');
        }
    }
    display_fridge(fridge);
    assert(fridge.food_count == 1);
    assert(is_string_equal(fridge.foods[0].food.name, mie_ayam.name));
    take_food(&fridge, 0, &mie_ayam);
    for (int i = 5; i < 5 + mie_ayam.size.width; i++) {
        for (int j = 5; j < 5 + mie_ayam.size.height; j++) {
            assert(fridge.space.mem[i][j] == '.');
        }
    }
    printf("\n");
    display_fridge(fridge);
    printf("All tests passed.\n");
    printf("\n")   ;
    printf("--- Driver Test Fridge ---");
    printf("\n")   ;
    printf("\n")   ;
}
