public class cautareBinaraParalela {
    int cautareBinaraParalela(int[] arr, int left, int right, int elem)
    {
        if (right >= left) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == elem)
                return mid;
            if (arr[mid] > elem)
                return cautareBinaraParalela(arr, left, mid - 1, elem);
            return cautareBinaraParalela(arr, mid + 1, right, elem);
        }
        return -1;
    }

    public static void main(String[] args) {
        cautareBinaraParalela obj = new cautareBinaraParalela();
        int[] array = {1, 2, 3, 10, 20, 30, 73, 80};
        int n = array.length;
        int elem = 73;
        int rez = obj.cautareBinaraParalela(array, 0, n - 1, elem);
        if (rez == -1)
            System.out.println("Elementul nu exista");
        else
            System.out.println("Elementul a fost gasit la indexul " + rez);
    }
}
