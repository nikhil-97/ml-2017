class Node {
    DataSet[] data;

    Node() {
        System.out.println("This is not allowed in Node");
    }

    Node(DataSet[] data) {
        this.data = data;
    }
}
