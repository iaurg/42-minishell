/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:04:24 by itaureli          #+#    #+#             */
/*   Updated: 2021/12/02 21:32:35 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do
  {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line();
    status = lsh_execute();

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  lsh_loop();
  return 0;
}