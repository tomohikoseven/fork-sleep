#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PNUM 8

int main(int argc, char** argv)
{
  pid_t pid;
  //pid_t pid[PNUM];
  int status = 0;
  int i = 0;
  
  memset( &pid, 0x00, sizeof(pid) );

  /// 新しいプロセスを作る
  /// カーネルは、同じプロセスをもう１つ作る
    pid = fork();
  #if 0
  for( i = 0; i < PNUM; i++ )
  {
    pid[i] = fork();
  }
  #endif

  /// プロセス作成に失敗した時は、0未満を返す
  if ( pid < 0 )
  {
    fprintf (stderr, "fork error\n");
    exit(1);
  }

  /// 子プロセスのpidは、0
  if (pid == 0) 
  {
    sleep(200);
    execl("/bin/echo", "echo", "hahaha", NULL);
    //perror("/bin/cat");
    exit(-1);
  }
  else
  {
    /// 子プロセスの終るのを待つ
    waitpid(pid, &status, 0);
    printf ("child(PID=%d) finished!\n", pid);

    
    if (WIFEXITED(status)){
      /// 子プロセスがexit以外で終了した場合は0を返す
      /// exitで終了した時は、0以外を返す
      printf("exit, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)){
      /// シグナルで終了していた時は0以外を返し、
      /// それ以外は、0を返す
      printf("signal, sig=%d\n", WTERMSIG(status));
    } else {
      printf("abnormal exit\n");
    }
    exit(0);
  }
  return(0);
}
