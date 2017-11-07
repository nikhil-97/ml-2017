import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

class Attribute {
    int index;
    static ArrayList<Set<String>> values;
    static String[] name;
    static boolean[] isSelected;
    static int totalNoOfAttributes = 15;

    static void createSetOfValues (DataSet[] data) {
        values = new ArrayList<>(totalNoOfAttributes-1);
        for (DataSet d: data) {
            for (int j=0; j<totalNoOfAttributes-1; j++) {
                Set<String> temp = new HashSet<>();
                if (values.get(j) != null) temp = values.get(j);
                temp.add(d.cell[j].value);
                values.add(j, temp);
            }
        }
    }

    static void makeAllFalse () {
        isSelected = new boolean[totalNoOfAttributes-1];
        for(boolean value: isSelected) value = false;
    }
    static void setNames(String[] names) {
        name = new String[Attribute.totalNoOfAttributes - 1];
        System.arraycopy(names, 0, name, 0, totalNoOfAttributes - 1);
    }
}
