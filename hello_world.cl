__kernel void hello_world_00(__global char* data) {
    int i=0;
    data[i++] = 'H';
    data[i++] = 'e';
    data[i++] = 'l';
    data[i++] = 'l';
    data[i++] = 'o';
    data[i++] = ' ';
    data[i++] = 'w';
    data[i++] = 'o';
    data[i++] = 'r';
    data[i++] = 'l';
    data[i++] = 'd';
    data[i++] = '!';
    data[i++] = '\n';
    data[i++] = 0;
}
