#include <stdio.h>


void f_degree(int n, int _graph[n][n], int in_degree[n]) {
    for (int i = 0; i < n; i++) {
        in_degree[i] = 0;
        for (int j = 0; j < n; j++) {
            in_degree[i] += _graph[j][i];
        }
    }
}

void f_out_degree(int n, int _graph[n][n], int out_degree[n]) {
    for (int i = 0; i < n; i++) {
        out_degree[i] = 0;
        for (int j = 0; j < n; j++) {
            out_degree[i] += _graph[i][j];
        }
    }
}


int f_v__h_degree(int n, int in_degree[n], int out_degree[n]) {
    int m_degree = 0;
    int v = -1;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] + out_degree[i] > m_degree) {
            m_degree = in_degree[i] + out_degree[i];
            v = i + 1;  
        }
    }

    return v;
}


int f_Indirect_p(int n, int _graph[n][n], int vi, int vj) {
    if (_graph[vi - 1][vj - 1]) {
        return 1; 
    }

    int p_l = 0;

    for (int k = 0; k < n; k++) {
        if (_graph[vi - 1][k]) {
            int l = f_Indirect_p(n, _graph, k + 1, vj);
            if (l > 0) {
                p_l = 1 + l;
                break;
            }
        }
    }

    return p_l;
}


int f_Isolated_v(int n, int _graph[n][n]) {
    for (int i = 0; i < n; i++) {
        int isolated = 1;
        for (int j = 0; j < n; j++) {
            if (_graph[i][j] || _graph[j][i]) {
                isolated = 0;
                break;
            }
        }
        if (isolated) {
            return i + 1; 
        }
    }

    return 0; 
}


int f_v_to_all(int n, int _graph[n][n]) {
    for (int i = 0; i < n; i++) {
        int connectedToAll = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && !_graph[i][j]) {
                connectedToAll = 0;
                break;
            }
        }
        if (connectedToAll) {
            return i + 1; 
        }
    }

    return 0; 
}

int main() {
    int n;

    
    printf("How many vertices?: ");
    scanf("%d", &n);

    
    int _graph[n][n];

    
    printf("Input matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &_graph[i][j]);
        }
    }

    
    printf("\nMenu:\n");
    printf("a. Find the in-degree of each v\n");
    printf("b. Find the out-degree of each v\n");
    printf("c. Find the v with highest degree (in + out)\n");
    printf("d. Find the l of the indirect path from v vi to v vj\n");
    printf("e. Find a v that is isolated\n");
    printf("f. Find a v that is directly connected to all other vertices\n");

    char choice;
    printf("Select from (a-f): ");
    scanf(" %c", &choice);

    switch (choice) {
        case 'a': {
            int in_degree[n];
            f_degree(n, _graph, in_degree);

            printf("v:");
            for (int i = 0; i < n; i++) {
                printf(" %d", i + 1);
            }
            printf("\nIn-degree:");
            for (int i = 0; i < n; i++) {
                printf(" %d", in_degree[i]);
            }
            printf("\n");
            break;
        }
        case 'b': {
            int out_degree[n];
            f_out_degree(n, _graph, out_degree);

            printf("v:");
            for (int i = 0; i < n; i++) {
                printf(" %d", i + 1);
            }
            printf("\nOut-degree:");
            for (int i = 0; i < n; i++) {
                printf(" %d", out_degree[i]);
            }
            printf("\n");
            break;
        }
        case 'c': {
            int in_degree[n], out_degree[n];
            f_degree(n, _graph, in_degree);
            f_out_degree(n, _graph, out_degree);

            int v = f_v__h_degree(n, in_degree, out_degree);
            if (v != -1) {
                printf("v %d has the highest degree (in + out).\n", v);
            } else {
                printf("No vertices found.\n");
            }
            break;
        }
        case 'd': {
            int vi, vj;
            printf("Input the source v (vi): ");
            scanf("%d", &vi);
            printf("Input the destination v (vj): ");
            scanf("%d", &vj);

            int l = f_Indirect_p(n, _graph, vi, vj);
            if (l > 0) {
                printf("l of the indirect h from v %d to v %d: %d\n", vi, vj, l);
            } else {
                printf("No indirect exists from v %d to v %d.\n", vi, vj);
            }
            break;
        }
        case 'e': {
            int isolated_v = f_Isolated_v(n, _graph);
            if (isolated_v != 0) {
                printf("v %d is isolated.\n", isolated_v);
            } else {
                printf("No isolated v found.\n");
            }
            break;
        }
        case 'f': {
            int v_to_all = f_v_to_all(n, _graph);
            if (v_to_all != 0) {
                printf("v %d has edges to all other vertices directly.\n", v_to_all);
            } else {
                printf("No v found.\n");
            }
            break;
        }
        default:
            printf("Invalid.\n");
    }

    return 0;
}
