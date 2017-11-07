class DecisionNode extends Node{
    boolean value;

    DecisionNode(boolean value, DataSet[] d) {
        this.value = value;
        this.data = d;
    }
}
