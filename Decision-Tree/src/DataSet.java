class DataSet {
    Cell[] cell;
    boolean targetAttribute;
    static int noOfExamples = 32561;

    DataSet(String buf){
        cell = new Cell[Attribute.totalNoOfAttributes-1];
        String temp[] = buf.split(",");
        for(int i=0; i<Attribute.totalNoOfAttributes-1; i++){
            cell[i] = new Cell(i, temp[i]);
        }
        this.targetAttribute = temp[Attribute.totalNoOfAttributes - 1].equals("1");
    }
}
