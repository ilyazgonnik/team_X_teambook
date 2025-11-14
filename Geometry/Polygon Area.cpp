int D_area_polygon(vector<pt> &polygon){
    pt zero; zero.x=0; zero.y=0;
    int ans=0; 
    int n=polygon.size();
    for(int i=0;i<n;i++){
        ans+=D_area(zero, polygon[i], polygon[(i+1)%n]);
    }
    return ans;
}//by the sign (can be + or -) DOUBLED!
