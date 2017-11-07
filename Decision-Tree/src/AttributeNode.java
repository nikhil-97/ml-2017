class AttributeNode extends Node{
    int index;
    String name;
    Path[] paths;

    AttributeNode(int index, String name, DataSet[] d) {
        this.index = index;
        this.name = name;
        this.data = d;
    }
}
