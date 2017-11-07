public class Main {
    public static void main(String args[]){
        String inputFile = "./data/adult_2.csv";
        String[] attributeNames = {"age", "work-class", "final-weight", "education", "education-num", "marital-status",
                "occupation", "relationship", "race", "sex", "capital-gain", "capital-loss", "hour-per-week",
                "native-country"};
        Attribute.setNames(attributeNames);
        Attribute.makeAllFalse();
        ReadInputFromFile f = new ReadInputFromFile(inputFile);
        f.readStoreData();
        Attribute.createSetOfValues(f.dataSetArr);
        ID3 id3Algorithm = new ID3(f.dataSetArr, 70);
        DTree decisionTree = new DTree();
        decisionTree.root = id3Algorithm.buildTree(id3Algorithm.d);
    }
}
