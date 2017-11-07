class Cell {
    int index;
    String value;

    Cell(int index, String value) {
        this.index = index;
        this.value = value;
        if (Attribute.isSelected[index]) Attribute.isSelected[index] = false;
    }
}
