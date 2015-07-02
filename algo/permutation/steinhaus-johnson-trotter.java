
public class DirectionalEntity implements Comparable<DirectionalEntity> {

  private String entity;

  private int dir; // can be -1 or 1 depending on the position

  public DirectionalEntity(String entity, int dir) {
    this.entity = entity;
    this.dir = dir;
  }

  public DirectionalEntity() {
    // TODO Auto-generated constructor stub
  }

  @Override
  public int compareTo(DirectionalEntity directionalEntity) {
    return (this.entity.compareTo(directionalEntity.entity));
  }

  public void reverseDir() {
    this.dir = dir * (-1);
  }

  public String getEntity() {
    return entity;
  }

  public int getDir() {
    return dir;
  }
}

public class Permutation {
  private List<DirectionalEntity> entityList = new ArrayList<DirectionalEntity>();
  private BigInteger numPermutations = new BigInteger("0");
  private ArrayList<DirectionalEntity> sortedList = new ArrayList<DirectionalEntity>();

  public Permutation(String str) {
    for(int x=0;x<str.length();x++) {
      DirectionalEntity entity = new DirectionalEntity(String.valueOf(str.charAt(x)), -1);
      entityList.add(entity);
    }

    Collections.sort(entityList);
    sortedList.addAll(entityList);
    Collections.reverse(sortedList);

    //1st Permutation: SortedList
    for(DirectionalEntity e : entityList) {
      System.out.print(e.getEntity()+" ");
    }
    System.out.println("");
    numPermutations = numPermutations.add(BigInteger.ONE);
  }

  public void  getPermutation() {
    while(true) {
      DirectionalEntity mobileDirectionalEntity = getMaxMobileDirectionalEntity();
      if(mobileDirectionalEntity == null) {
        // all permutations have been found
        System.out.println("Total permutations: "+numPermutations);
        break;
      }
      if(mobileDirectionalEntity.getDir() == 1) {
        // Swap this with the right element in the list
        int positionInOriginalList = entityList.indexOf(mobileDirectionalEntity);
        entityList.set(positionInOriginalList, entityList.get(positionInOriginalList+1));
        entityList.set(positionInOriginalList+1, mobileDirectionalEntity);
      }
      else {
        // Swap this with the left element in the list
        int positionInOriginalList = entityList.indexOf(mobileDirectionalEntity);
        entityList.set(positionInOriginalList, entityList.get(positionInOriginalList-1));
        entityList.set(positionInOriginalList-1, mobileDirectionalEntity);
      }

      // We have got a unique permutation - print this
      for(DirectionalEntity e : entityList) {
        System.out.print(e.getEntity()+" ");
      }

      System.out.println("");
      numPermutations = numPermutations.add(BigInteger.ONE);

      // Now reverse the direction of all the numbers greater than mobileDirectionalNumber
      for(DirectionalEntity e : entityList) {
        if(mobileDirectionalEntity.compareTo(e) < 0)
        e.reverseDir();
      }
    }
  }

  /**
  * Gets the maximum mobile directional number by checking
  * the numbers in decreasing order of magnitude
  * @return max mobileDirectionalNumber, if it is exist, else null
  */
  private DirectionalEntity getMaxMobileDirectionalEntity() {
    for(DirectionalEntity dirEntity : sortedList) {
      DirectionalEntity maxDirEntity = dirEntity;
      // Now check for the position of maxDirNum in original List
      // to see if this maxDirNum is actually a mobile directional number
      int positionInOriginalList = entityList.indexOf(maxDirEntity);
      if ((maxDirEntity.getDir() == -1 && (positionInOriginalList != 0 &&
        entityList.get(positionInOriginalList-1).compareTo(maxDirEntity) < 0)
        || (maxDirEntity.getDir() == 1 && (positionInOriginalList != entityList.size()-1 && entityList.get(positionInOriginalList+1).compareTo(maxDirEntity) < 0)))) {
      // This is the max mobile directional number - return this
        return maxDirEntity;
      }
    }
    return null; // No more mobile directional numbers exist. All the permutations have been found.
   }
}
