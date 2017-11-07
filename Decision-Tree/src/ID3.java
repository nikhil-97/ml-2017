import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class ID3 {
    DataSet[] d;

    ID3(DataSet[] d, float percent) {
        int length;
        length = (int)percent*(DataSet.noOfExamples)/100;
        System.arraycopy(d, 0, this.d, 0, length);
    }

    Node buildTree(DataSet[] d) {
        Node temp = new Node(d);
        int checkForAllPosOrNeg = allPosOrNeg(d);
        if(checkForAllPosOrNeg == 1) {
            temp = new DecisionNode(true, d);
            return temp;
        }
        else if(checkForAllPosOrNeg == -1) {
            temp = new DecisionNode(false, d);
            return temp;
        }
        int index = getBestAttribute(d);
        if(index != -1) {
            if(!splitDataSetOn(temp, d, index)) {
                System.out.println("Error occurred while splitting attribute at index " + Integer.toString(index));
                System.exit(1);
            }
        }
        else {
            if(checkForAllPosOrNeg == 2) {
                temp = new DecisionNode(true, d);
                return temp;
            }
            else {
                temp = new DecisionNode(false, d);
                return temp;
            }
        }
        return temp;
    }
    
    private int allPosOrNeg(DataSet[] d) {
        int posCount = 0, negCount = 0;
        for (DataSet t:
             d) {
            if(t.targetAttribute) posCount++;
            else negCount++;
        }
        if (posCount == d.length) return 1;
        if (negCount == d.length) return -1;
        if(posCount >= negCount) return 2;
        return -2;
    }

    private int getBestAttribute(DataSet[] d) {
        float minEntropy = Float.MAX_VALUE;
        int minEntropyIndex = -1;
        for(int i=0; i<Attribute.totalNoOfAttributes - 1; i++) {
            if(Attribute.isSelected[i]) continue;
            float tempEntropy = getEntropy(d, i);
            if(tempEntropy <= minEntropy) {
                minEntropy = tempEntropy;
                minEntropyIndex = i;
            }
        }
        return minEntropyIndex;
    }

    private float getEntropy(DataSet[] d, int index) {
        float ans = 0;
        int totalAttrs = 0, dataSetLength = d.length;
        for (int i=0; i<Attribute.totalNoOfAttributes-1; i++) {
            if (i == index || Attribute.isSelected[i]) continue;
            totalAttrs++;
        }
        float[] probOfAttr = new float[totalAttrs];
        for (int i=0; i<Attribute.totalNoOfAttributes-1; i++) {
            if (i == index || Attribute.isSelected[i]) continue;
            int size = Attribute.values.get(i).size();
            Probability[] prob = new Probability[size];
            for (int j = 0; j < size; j++) {
                prob[j] = new Probability();
                for (DataSet t : d) {
                    if (Attribute.values.get(i).contains(t.cell[i].value)) {
                        prob[j].totalCount++;
                        if (t.targetAttribute) prob[j].inFavor++;
                    }
                }
                prob[j].probAns = prob[j].inFavor / prob[j].totalCount;
            }
            probOfAttr[i] = 0;
            for (int j = 0; j < size; j++) {
                probOfAttr[i] += (prob[j].probAns * prob[j].totalCount / dataSetLength);
            }
            ans+=(-probOfAttr[i]*Math.log(probOfAttr[i]));
        }
        return ans;
    }

    private boolean splitDataSetOn(Node temp, DataSet[] d, int index) {
        int noOfListDataSets = Attribute.values.get(index).size();
        ArrayList<ArrayList<DataSet>> dataSetsList = new ArrayList<>(noOfListDataSets);
        String[] values = Attribute.values.get(index).toArray(new String[noOfListDataSets]);
        List<String> valuesList = Arrays.asList(values);
        for (DataSet t: d) {
            int i = valuesList.indexOf(t.cell[index].value);
            ArrayList<DataSet> DataSetOfI = dataSetsList.get(i);
            DataSetOfI.add(t);
            dataSetsList.add(DataSetOfI);
        }
        DataSet[][] dataSetsArray = new DataSet[noOfListDataSets][];
        for (int i=0; i<noOfListDataSets; i++) {
            dataSetsList.get(i).toArray(dataSetsArray[i]);
        }
        Attribute.isSelected[index] = true;
        ((AttributeNode) temp).paths = new Path[noOfListDataSets];
        for (int i=0; i<noOfListDataSets; i++) {
            ((AttributeNode)temp).paths[i].child = buildTree(dataSetsArray[i]);
            ((AttributeNode)temp).paths[i].value = valuesList.get(i);
        }
        return true;
    }
}
